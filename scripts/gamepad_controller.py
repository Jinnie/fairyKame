#!/usr/bin/env python3
"""
FairyKame Gamepad Controller
Interactive, game-style keyboard controller for FairyKame robot over USB Serial.

Features:
  - Hold-to-move controls (W/A/S/D, diagonals, strafe with ',' and '.')
  - Instant stop (0ms lag) the moment keys are released
  - Supports diagonal key combinations (e.g., W+A = Forward-Left)
  - Direct number keys (0-9) and letter shortcuts for expressive tricks and poses
  - Automatic COM port detection
  - Zero third-party dependencies required on Windows (uses built-in ctypes)
"""

import sys
import time
import os
import argparse
import threading

try:
    import serial
    import serial.tools.list_ports
    HAS_SERIAL = True
except ImportError:
    HAS_SERIAL = False


class SerialTransport:
    def __init__(self, port: str, baudrate: int = 115200):
        if not HAS_SERIAL:
            raise RuntimeError("pyserial is required. Install with: pip install pyserial")
        print(f"[Serial] Connecting to {port} @ {baudrate} baud...")
        self.ser = serial.Serial(port, baudrate, timeout=0.1)
        time.sleep(1.5)  # Wait for ESP8266 to reset/stabilize
        print(f"[Serial] Connected to {port}!")

        # Background reader to keep incoming serial buffer clear
        self._running = True
        self._reader_thread = threading.Thread(target=self._read_loop, daemon=True)
        self._reader_thread.start()

    def _read_loop(self):
        while self._running:
            try:
                line = self.ser.readline()
                if line:
                    decoded = line.decode('utf-8', errors='ignore').strip()
                    if decoded.startswith('#'):
                        # Robot status update from Mind
                        pass
            except Exception:
                break

    def send_command(self, cmd_name: str, cmd_char: str):
        if self.ser and self.ser.is_open:
            try:
                if len(cmd_char) == 1:
                    self.ser.write(cmd_char.encode('ascii'))
                else:
                    self.ser.write(f"\n{cmd_name}\n".encode('ascii'))
                self.ser.flush()
            except Exception as e:
                print(f"[Serial Error] {e}")

    def close(self):
        self._running = False
        if self.ser and self.ser.is_open:
            try:
                self.ser.write(b' ')  # stop
                self.ser.flush()
                self.ser.close()
            except Exception:
                pass


class KeyPoller:
    """Detects real-time key states (down/up) using Windows ctypes."""
    def __init__(self):
        self.is_windows = os.name == 'nt'
        if self.is_windows:
            import ctypes
            self.user32 = ctypes.windll.user32
            self.VK = {
                'W': 0x57, 'A': 0x41, 'S': 0x53, 'D': 0x44,
                'Q': 0x51, 'E': 0x45, 'Z': 0x5A, 'C': 0x43,
                'COMMA': 0xBC, 'PERIOD': 0xBE,
                'SPACE': 0x20, 'ESCAPE': 0x1B,
                '0': 0x30, '1': 0x31, '2': 0x32, '3': 0x33, '4': 0x34,
                '5': 0x35, '6': 0x36, '7': 0x37, '8': 0x38, '9': 0x39,
                'M': 0x4D, 'P': 0x50, 'K': 0x4B, 'H': 0x48, 'R': 0x52
            }
        else:
            self.user32 = None

    def is_down(self, key_name: str) -> bool:
        if self.is_windows and self.user32:
            code = self.VK.get(key_name)
            if code is None:
                return False
            return bool(self.user32.GetAsyncKeyState(code) & 0x8000)
        return False


def auto_detect_serial_port() -> str:
    """Finds an ESP8266 / NodeMCU serial port."""
    if not HAS_SERIAL:
        return "COM6"
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        desc = (p.description or "").lower()
        if "cp210" in desc or "ch340" in desc or "usb-to-uart" in desc or "nodemcu" in desc:
            return p.device
    if ports:
        return ports[0].device
    return "COM6"


BANNER = r"""
  ___     _          _  __                  
 | __|_ _(_)_ _ _  _| |/ /__ _ _ __  ___    
 | _/ _` | | '_| || | ' </ _` | '  \/ -_)   
 |_|\__,_|_|_|  \_, |_|\_\__,_|_|_|_\___|   
                |__/                        
  >>> Computer-Game Keyboard Controller <<<
"""

HELP_TEXT = """
[ Locomotion ] (Hold to Move - Release to Stop Instantly)
    W / S          : Forward / Backward
    A / D          : Turn Left / Turn Right
    W+A / W+D      : Diagonal Up-Left / Up-Right
    S+A / S+D      : Diagonal Down-Left / Down-Right
    Q / E          : Dedicated Diagonal Up-Left / Up-Right
    Z / C          : Dedicated Diagonal Down-Left / Down-Right
    < , > / < . >  : Strafe Left (,) / Strafe Right (.)

[ Tricks & Poses ] (Tap Key)
    1: Dance       2: Push Ups    3: Sit         4: Crawl
    5: Tiptoe      6 / H: Say Hi  7: Tap Foot    8: Play Dead
    9: Shiver      0: Pack        P: Pounce      K: Scratch Ear
    R: Recover     M: Magic       Space: Stop

[ Quit ]
    Escape or Ctrl+C
"""


def main():
    parser = argparse.ArgumentParser(description="FairyKame Gamepad Controller (USB Serial)")
    parser.add_argument("--port", default=None, help="Serial COM port (default: auto-detected, e.g. COM6)")
    parser.add_argument("--baud", type=int, default=115200, help="Serial baud rate (default: 115200)")
    args = parser.parse_args()

    port = args.port or auto_detect_serial_port()
    try:
        transport = SerialTransport(port, args.baud)
    except Exception as e:
        print(f"[Error] Failed to open serial port {port}: {e}")
        sys.exit(1)

    poller = KeyPoller()
    if not poller.is_windows:
        print("[Notice] Non-Windows OS detected. Native low-latency keyboard polling requires Windows.")
        print("Please run this on Windows for full game-controller functionality.")
        transport.close()
        sys.exit(1)

    print(BANNER)
    print(f"Connected to: {port} @ {args.baud} baud")
    print(HELP_TEXT)
    print("Controller is ACTIVE. Start pressing WASD / keys...\n")

    current_command = "stop"
    last_trick_key = None
    last_keepalive_time = 0.0

    try:
        while True:
            # Check for exit
            if poller.is_down('ESCAPE'):
                print("\n[Exit] Escape pressed. Shutting down...")
                break

            # Check directional movement keys
            w = poller.is_down('W')
            s = poller.is_down('S')
            a = poller.is_down('A')
            d = poller.is_down('D')
            q = poller.is_down('Q')
            e = poller.is_down('E')
            z = poller.is_down('Z')
            c = poller.is_down('C')
            comma = poller.is_down('COMMA')
            period = poller.is_down('PERIOD')
            space = poller.is_down('SPACE')

            desired_move = None
            cmd_char = ' '

            if space:
                desired_move = "stop"
                cmd_char = ' '
            elif comma:
                desired_move = "strafeLeft"
                cmd_char = ','
            elif period:
                desired_move = "strafeRight"
                cmd_char = '.'
            elif (w and a) or q:
                desired_move = "upLeft"
                cmd_char = 'q'
            elif (w and d) or e:
                desired_move = "upRight"
                cmd_char = 'e'
            elif (s and a) or z:
                desired_move = "backLeft"
                cmd_char = 'z'
            elif (s and d) or c:
                desired_move = "backRight"
                cmd_char = 'c'
            elif w:
                desired_move = "run"
                cmd_char = 'w'
            elif s:
                desired_move = "back"
                cmd_char = 's'
            elif a:
                desired_move = "turnL"
                cmd_char = 'a'
            elif d:
                desired_move = "turnR"
                cmd_char = 'd'

            # Movement state change (hold to move, release to stop)
            if desired_move is not None:
                now = time.time()
                should_send = False
                if desired_move != current_command:
                    should_send = True
                    print(f"\rStatus: >> [{cmd_char.upper()}] {desired_move:<15}", end="", flush=True)
                elif (now - last_keepalive_time >= 0.05):
                    # Stream keepalive pulses every 50ms to satisfy firmware watchdog while held
                    should_send = True

                if should_send:
                    current_command = desired_move
                    last_keepalive_time = now
                    transport.send_command(current_command, cmd_char)
            else:
                # No movement key pressed
                if current_command in ["run", "back", "turnL", "turnR", "upLeft", "upRight", 
                                       "backLeft", "backRight", "strafeLeft", "strafeRight"]:
                    # Key was just released! Stop immediately.
                    current_command = "stop"
                    transport.send_command("stop", ' ')
                    print(f"\rStatus: .. [ ] STOPPED        ", end="", flush=True)

                # Check one-shot trick keys
                trick_map = {
                    '1': ('dance', '1'),
                    '2': ('pushUps', '2'),
                    '3': ('sit', '3'),
                    '4': ('crawl', '4'),
                    '5': ('tiptoe', '5'),
                    '6': ('sayHi', '6'),
                    '7': ('tapFoot', '7'),
                    '8': ('playDead', '8'),
                    '9': ('shiver', '9'),
                    '0': ('pack', '0'),
                    'P': ('pouncePrep', 'p'),
                    'K': ('scratchEar', 'k'),
                    'H': ('sayHi', 'h'),
                    'R': ('recover', 'r'),
                    'M': ('magic', 'm'),
                }
                
                pressed_trick = None
                for key_name, (trick_cmd, char_code) in trick_map.items():
                    if poller.is_down(key_name):
                        pressed_trick = (trick_cmd, char_code)
                        break

                if pressed_trick and pressed_trick != last_trick_key:
                    trick_cmd, char_code = pressed_trick
                    current_command = trick_cmd
                    transport.send_command(trick_cmd, char_code)
                    print(f"\rStatus: ** [!] {trick_cmd:<15}", end="", flush=True)
                    last_trick_key = pressed_trick
                elif not pressed_trick:
                    last_trick_key = None

            time.sleep(0.02)  # 50 Hz poll rate (20ms)

    except KeyboardInterrupt:
        print("\n[Exit] Interrupted by user.")
    finally:
        print("\nStopping robot and cleaning up...")
        if transport:
            transport.send_command("stop", ' ')
            transport.close()
        print("Done. Goodbye!")


if __name__ == "__main__":
    main()
