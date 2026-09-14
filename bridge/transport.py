"""
FairyKame Transport Abstraction Layer
Supports both Wi-Fi (HTTP) and USB Serial (UART) communications.
"""

from abc import ABC, abstractmethod
import os
import time
import socket
import logging
from typing import Optional, Dict, Any

try:
    import requests
except ImportError:
    requests = None

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    serial = None

logger = logging.getLogger("fairykame.transport")


class RobotTransport(ABC):
    """Abstract base class for robot communication channels."""

    @abstractmethod
    def send_command(self, cmd: str) -> bool:
        """Send a gait or trick command to the robot."""
        pass

    @abstractmethod
    def send_trim(self, val: int) -> bool:
        """Adjust overall height trim (-90 to +90)."""
        pass

    @abstractmethod
    def send_tilt(self, val: int) -> bool:
        """Adjust lateral tilt (-90 to +90)."""
        pass

    @abstractmethod
    def send_speed(self, val: int) -> bool:
        """Adjust speed modifier (-5 to +5)."""
        pass

    @abstractmethod
    def send_delay(self, val: int) -> bool:
        """Adjust tick delay in ms (1 to 50)."""
        pass

    @abstractmethod
    def get_status(self) -> Dict[str, Any]:
        """Query connection health and telemetry."""
        pass

    def run_for_duration(self, cmd: str, duration: float) -> bool:
        """Execute a momentary command for specified duration, then stop."""
        success = self.send_command(cmd)
        if not success:
            return False
        time.sleep(max(0.1, duration))
        return self.send_command("stop")

    @abstractmethod
    def close(self) -> None:
        """Release underlying resources."""
        pass


class WiFiTransport(RobotTransport):
    """Wi-Fi HTTP transport communicating with FairyKame REST endpoints."""

    def __init__(self, base_url: str = "http://fairy.local", timeout: float = 3.0):
        if requests is None:
            raise ImportError("The 'requests' package is required for WiFiTransport. Install with 'pip install requests'.")

        self.original_url = base_url.rstrip("/")
        self.base_url = self.original_url
        self.timeout = timeout
        self.session = requests.Session()
        self.resolved_ip: Optional[str] = None

        # Resolve hostname once to avoid repetitive mDNS multicast delays on Windows
        self._resolve_host()

    def _resolve_host(self) -> None:
        """Attempt to resolve mDNS hostname to IP to accelerate subsequent HTTP calls."""
        try:
            parsed = self.original_url.replace("http://", "").replace("https://", "").split(":")[0]
            ip = socket.gethostbyname(parsed)
            self.resolved_ip = ip
            # Keep original hostname for Host header, but we can talk to IP directly if preferred
            logger.info(f"Resolved {parsed} to {ip}")
        except Exception as e:
            logger.debug(f"Could not pre-resolve {self.original_url}: {e}")

    def _get(self, endpoint: str, params: Optional[Dict[str, Any]] = None) -> bool:
        url = f"{self.base_url}/{endpoint.lstrip('/')}"
        try:
            resp = self.session.get(url, params=params, timeout=self.timeout)
            return resp.status_code == 200
        except Exception as e:
            # Fallback to direct IP if hostname lookup failed
            if self.resolved_ip and self.base_url != f"http://{self.resolved_ip}":
                try:
                    fallback_url = f"http://{self.resolved_ip}/{endpoint.lstrip('/')}"
                    resp = self.session.get(fallback_url, params=params, timeout=self.timeout)
                    if resp.status_code == 200:
                        self.base_url = f"http://{self.resolved_ip}"
                        return True
                except Exception:
                    pass
            logger.error(f"WiFi GET failed ({url}): {e}")
            return False

    def send_command(self, cmd: str) -> bool:
        return self._get("cmd", {"command": cmd})

    def send_trim(self, val: int) -> bool:
        clamped = max(-90, min(90, int(val)))
        return self._get("trim", {"trim": clamped})

    def send_tilt(self, val: int) -> bool:
        clamped = max(-90, min(90, int(val)))
        return self._get("tilt", {"tilt": clamped})

    def send_speed(self, val: int) -> bool:
        clamped = max(-5, min(5, int(val)))
        return self._get("speed", {"speed": clamped})

    def send_delay(self, val: int) -> bool:
        clamped = max(1, min(100, int(val)))
        return self._get("delay", {"delay": clamped})

    def get_status(self) -> Dict[str, Any]:
        t0 = time.time()
        ok = False
        try:
            resp = self.session.get(f"{self.base_url}/", timeout=2.0)
            ok = resp.status_code == 200
        except Exception:
            ok = False
        latency = (time.time() - t0) * 1000.0

        return {
            "transport": "wifi",
            "online": ok,
            "url": self.base_url,
            "resolved_ip": self.resolved_ip,
            "latency_ms": round(latency, 1) if ok else None
        }

    def close(self) -> None:
        if self.session:
            self.session.close()


class SerialTransport(RobotTransport):
    """USB Serial UART transport communicating with FairyKame."""

    KEY_MAP = {
        "stop": b" ",
        "relax": b" ",
        "run": b"W",
        "back": b"S",
        "turnL": b"A",
        "turnR": b"D",
        "upLeft": b"Q",
        "upRight": b"E",
        "backLeft": b"Z",
        "backRight": b"C",
        "strafeLeft": b",",
        "strafeRight": b".",
        "dance": b"1",
        "pushUps": b"2",
        "sit": b"3",
        "crawl": b"4",
        "tiptoe": b"5",
        "sayHi": b"6",
        "tapFoot": b"7",
        "playDead": b"8",
        "shiver": b"9",
        "pack": b"0",
        "pouncePrep": b"P",
        "scratchEar": b"K",
        "recover": b"R",
        "magic": b"M",
    }

    def __init__(self, port: Optional[str] = None, baudrate: int = 115200):
        if serial is None:
            raise ImportError("The 'pyserial' package is required for SerialTransport. Install with 'pip install pyserial'.")

        self.baudrate = baudrate
        self.port = port or self.auto_detect_port()
        if not self.port:
            raise RuntimeError("No serial port specified and no compatible CP210x/CH340/ESP device auto-detected.")

        self.ser = serial.Serial(self.port, self.baudrate, timeout=0.5)
        time.sleep(0.5)  # Let connection stabilize

    @classmethod
    def auto_detect_port(cls) -> Optional[str]:
        """Attempt to discover FairyKame USB UART port."""
        if serial is None:
            return None
        ports = serial.tools.list_ports.comports()
        for p in ports:
            desc = (p.description or "").lower()
            if any(k in desc for k in ["cp210", "ch340", "ftdi", "uart", "usb serial"]):
                return p.device
        # Fallback to last detected COM port on Windows if available
        if ports:
            return ports[-1].device
        return None

    def send_command(self, cmd: str) -> bool:
        if not self.ser or not self.ser.is_open:
            return False
        try:
            if cmd in self.KEY_MAP:
                self.ser.write(self.KEY_MAP[cmd])
            else:
                # Type full command name via Enter prompt
                self.ser.write(b"\n" + cmd.encode("ascii", errors="ignore") + b"\n")
            self.ser.flush()
            return True
        except Exception as e:
            logger.error(f"Serial send_command failed: {e}")
            return False

    def send_trim(self, val: int) -> bool:
        # Serial protocol does not yet have dedicated trim keys, sends full command fallback
        logger.warning("Trim via Serial not directly mapped to key; use Wi-Fi or extended protocol.")
        return False

    def send_tilt(self, val: int) -> bool:
        logger.warning("Tilt via Serial not directly mapped to key; use Wi-Fi or extended protocol.")
        return False

    def send_speed(self, val: int) -> bool:
        logger.warning("Speed via Serial not directly mapped to key; use Wi-Fi or extended protocol.")
        return False

    def send_delay(self, val: int) -> bool:
        logger.warning("Delay via Serial not directly mapped to key; use Wi-Fi or extended protocol.")
        return False

    def run_for_duration(self, cmd: str, duration: float) -> bool:
        """Keep momentary command alive by repeating key every 100ms (watchdog is ~200ms)."""
        key = self.KEY_MAP.get(cmd)
        if not key:
            # Persistent trick
            self.send_command(cmd)
            time.sleep(duration)
            return self.send_command("stop")

        end_time = time.time() + max(0.1, duration)
        while time.time() < end_time:
            self.ser.write(key)
            self.ser.flush()
            time.sleep(0.1)

        # Space to stop
        self.ser.write(b" ")
        self.ser.flush()
        return True

    def get_status(self) -> Dict[str, Any]:
        is_open = self.ser is not None and self.ser.is_open
        return {
            "transport": "serial",
            "online": is_open,
            "port": self.port,
            "baudrate": self.baudrate
        }

    def close(self) -> None:
        if self.ser and self.ser.is_open:
            self.ser.close()


def get_transport(
    mode: str = "auto",
    wifi_url: str = "http://fairy.local",
    serial_port: Optional[str] = None
) -> RobotTransport:
    """
    Factory function to initialize the preferred transport.
    mode: 'auto', 'wifi', or 'serial' (can be overridden by FAIRYKAME_TRANSPORT env var).
    """
    chosen_mode = os.environ.get("FAIRYKAME_TRANSPORT", mode).lower()
    env_url = os.environ.get("FAIRYKAME_URL", wifi_url)
    env_port = os.environ.get("FAIRYKAME_PORT", serial_port)

    if chosen_mode == "wifi":
        return WiFiTransport(base_url=env_url)

    if chosen_mode == "serial":
        return SerialTransport(port=env_port)

    # AUTO mode: Try Wi-Fi first, fallback to Serial
    logger.info("Auto-detecting transport channel...")
    try:
        wifi = WiFiTransport(base_url=env_url, timeout=1.5)
        status = wifi.get_status()
        if status.get("online"):
            logger.info(f"Connected to FairyKame via Wi-Fi ({env_url})")
            return wifi
        wifi.close()
    except Exception as e:
        logger.debug(f"Wi-Fi probe skipped/failed: {e}")

    logger.info("Wi-Fi not reachable, probing USB Serial...")
    try:
        ser = SerialTransport(port=env_port)
        logger.info(f"Connected to FairyKame via Serial ({ser.port})")
        return ser
    except Exception as e:
        logger.warning(f"Serial probe failed: {e}")

    # Default to WiFiTransport instance even if offline so user sees actionable URLs
    logger.warning("Neither transport responded immediately; defaulting to WiFiTransport.")
    return WiFiTransport(base_url=env_url)
