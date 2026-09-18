#!/usr/bin/env python3
"""
FairyKame Gamepad Controller (Dynamic MoveSpecs & Predefined Library Switcher)
------------------------------------------------------------------------------
Interactive, low-latency keyboard controller for FairyKame over USB Serial or Wi-Fi.

Features:
  - Dynamically reads the specs/ folder and maps MoveSpecs directly to action keys.
  - Seamless Tab switching between [Dynamic MoveSpecs] and [Predefined Firmware Moves].
  - Live folder watching: Automatically picks up new/edited .json files in specs/.
  - Multi-bank pagination with '[' and ']' if specs exceed available hotkeys.
  - Low-latency hold-to-move WASD locomotion with instant dead-man's stop on release.
  - Dual transport: Works seamlessly over USB Serial or local Wi-Fi (http://fairy.local).
"""

import sys
import os
import time
import json
import argparse
import threading

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from bridge.transport import get_transport, RobotTransport, WiFiTransport, SerialTransport

# 20 direct hotkeys assigned to dynamic MoveSpec slots (no conflicts with WASD/QEZC/,/.)
SLOT_KEYS = [
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'P', 'K', 'M', 'H', 'R', 'U', 'I', 'O', 'J', 'B'
]

# Classic firmware baked-in tricks mapping
PREDEFINED_MAP = {
    '1': 'dance',
    '2': 'pushUps',
    '3': 'sit',
    '4': 'crawl',
    '5': 'tiptoe',
    '6': 'sayHi',
    '7': 'tapFoot',
    '8': 'playDead',
    '9': 'shiver',
    '0': 'pack',
    'P': 'pouncePrep',
    'K': 'scratchEar',
    'H': 'sayHi',
    'R': 'recover',
    'M': 'magic',
}

class KeyPoller:
    """Detects real-time key states and transitions using Windows ctypes."""
    def __init__(self):
        self.is_windows = os.name == 'nt'
        self._prev_state = {}
        self._curr_state = {}

        if self.is_windows:
            import ctypes
            self.user32 = ctypes.windll.user32
            self.VK = {
                'W': 0x57, 'A': 0x41, 'S': 0x53, 'D': 0x44,
                'Q': 0x51, 'E': 0x45, 'Z': 0x5A, 'C': 0x43,
                'COMMA': 0xBC, 'PERIOD': 0xBE,
                'SPACE': 0x20, 'ESCAPE': 0x1B,
                'TAB': 0x09, 'RETURN': 0x0D,
                'LBRACKET': 0xDB, 'RBRACKET': 0xDD, 'BACKSLASH': 0xDC,
                # Alphanumeric hotkeys
                '0': 0x30, '1': 0x31, '2': 0x32, '3': 0x33, '4': 0x34,
                '5': 0x35, '6': 0x36, '7': 0x37, '8': 0x38, '9': 0x39,
                'P': 0x50, 'K': 0x4B, 'M': 0x4D, 'H': 0x48, 'R': 0x52,
                'U': 0x55, 'I': 0x49, 'O': 0x4F, 'J': 0x4A, 'B': 0x42
            }
        else:
            self.user32 = None
            self.VK = {}

    def update(self):
        """Polls current physical state of all tracked keys."""
        self._prev_state = self._curr_state.copy()
        if self.is_windows and self.user32:
            for key, code in self.VK.items():
                self._curr_state[key] = bool(self.user32.GetAsyncKeyState(code) & 0x8000)

    def is_down(self, key_name: str) -> bool:
        """Returns True if the key is currently held down."""
        return self._curr_state.get(key_name, False)

    def just_pressed(self, key_name: str) -> bool:
        """Returns True only on the leading-edge transition (single tick)."""
        return self._curr_state.get(key_name, False) and not self._prev_state.get(key_name, False)


class SpecManager:
    """Manages dynamic discovery, parsing, and live watching of the specs/ folder."""
    def __init__(self, specs_dir: str):
        self.specs_dir = specs_dir
        self._last_mtime = 0
        self.specs = []
        self.rescan(force=True)

    def rescan(self, force: bool = False) -> bool:
        """Scans specs/ directory for valid MoveSpec JSONs. Returns True if updated."""
        if not os.path.exists(self.specs_dir):
            return False

        try:
            mtime = os.path.getmtime(self.specs_dir)
        except Exception:
            mtime = 0

        if not force and mtime == self._last_mtime and self.specs:
            return False

        self._last_mtime = mtime
        new_specs = []

        for fname in sorted(os.listdir(self.specs_dir)):
            if fname.endswith(".json") and fname != "calibration.json":
                fpath = os.path.join(self.specs_dir, fname)
                try:
                    with open(fpath, "r", encoding="utf-8") as f:
                        data = json.load(f)
                    if "fl" in data and "fr" in data:
                        name = data.get("name", os.path.splitext(fname)[0])
                        desc = data.get("description", "Dynamic MoveSpec").strip()
                        summary = desc.split("\n")[0]
                        if len(summary) > 55:
                            summary = summary[:52] + "..."
                        new_specs.append({
                            "name": name,
                            "description": summary,
                            "filename": fname,
                            "data": data
                        })
                except Exception:
                    continue

        self.specs = new_specs
        return True


BANNER = r"""
  ___     _          _  __                  
 | __|_ _(_)_ _ _  _| |/ /__ _ _ __  ___    
 | _/ _` | | '_| || | ' </ _` | '  \/ -_)   
 |_|\__,_|_|_|  \_, |_|\_\__,_|_|_|_\___|   
                |__/                        
  >>> Computer-Game Keyboard Controller <<<
"""


def render_board(mode: str, spec_manager: SpecManager, bank_idx: int):
    """Renders the current active keybinding board."""
    print("\n" + "=" * 80)
    if mode == "DYNAMIC":
        total_specs = len(spec_manager.specs)
        per_page = len(SLOT_KEYS)
        total_banks = max(1, (total_specs + per_page - 1) // per_page)
        start_idx = bank_idx * per_page
        bank_specs = spec_manager.specs[start_idx : start_idx + per_page]

        print(f" >>> ACTIVE LIBRARY: [ DYNAMIC MOVESPECS ({total_specs} Loaded) ] <<<")
        print(f" Bank {bank_idx + 1}/{total_banks} (Press '[' and ']' to change bank | Press TAB for Predefined)")
        print("-" * 80)

        # Print specs 4 per row
        row = []
        for i, key in enumerate(SLOT_KEYS):
            if i < len(bank_specs):
                spec = bank_specs[i]
                row.append(f"[{key}] {spec['name']:<14}")
            else:
                row.append(f"[{key}] (empty)       ")
            if len(row) == 4:
                print("  " + "  ".join(row))
                row = []
        if row:
            print("  " + "  ".join(row))

    else:
        print(" >>> ACTIVE LIBRARY: [ PREDEFINED FIRMWARE MOVES ] <<<")
        print(" Classic Baked-in Gaits (Press TAB to switch to Dynamic Specs)")
        print("-" * 80)
        items = list(PREDEFINED_MAP.items())
        row = []
        for key, cmd in items:
            row.append(f"[{key}] {cmd:<14}")
            if len(row) == 4:
                print("  " + "  ".join(row))
                row = []
        if row:
            print("  " + "  ".join(row))

    print("-" * 80)
    print(" Controls: Hold WASD/Q/E/Z/C/,/. to drive | SPACE: Stop | ESC: Quit")
    print("=" * 80 + "\n")


def main():
    parser = argparse.ArgumentParser(description="FairyKame Gamepad Controller (Dynamic Specs & Predefined Switcher)")
    parser.add_argument("--transport", "-t", choices=["auto", "wifi", "serial"], default="auto", help="Transport mode (default: auto)")
    parser.add_argument("--port", "-p", default=None, help="Serial COM port (default: auto-detected, e.g. COM6)")
    parser.add_argument("--baud", "-b", type=int, default=115200, help="Serial baud rate (default: 115200)")
    parser.add_argument("--url", default="http://fairy.local", help="Wi-Fi base URL (default: http://fairy.local)")
    parser.add_argument("--mode", "-m", choices=["dynamic", "predefined"], default="dynamic", help="Initial library mode (default: dynamic)")
    args = parser.parse_args()

    # Initialize dynamic spec manager
    specs_dir = os.path.join(PROJECT_ROOT, "specs")
    spec_mgr = SpecManager(specs_dir)

    print(f"Connecting to FairyKame ({args.transport})...")
    try:
        robot = get_transport(mode=args.transport, base_url=args.url, serial_port=args.port, baudrate=args.baud)
    except Exception as e:
        print(f"[Error] Failed to connect to robot: {e}")
        sys.exit(1)

    # Optional background drain thread if USB Serial
    if isinstance(robot, SerialTransport) and robot.ser and robot.ser.is_open:
        def _drain_serial():
            while robot.ser and robot.ser.is_open:
                try:
                    robot.ser.readline()
                except Exception:
                    break
        t = threading.Thread(target=_drain_serial, daemon=True)
        t.start()

    poller = KeyPoller()
    if not poller.is_windows:
        print("[Notice] Non-Windows OS detected. Low-latency ctypes keyboard polling requires Windows.")
        robot.close()
        sys.exit(1)

    print(BANNER)
    trans_desc = f"Wi-Fi ({args.url})" if isinstance(robot, WiFiTransport) else f"Serial ({getattr(robot, 'port', 'UART')} @ {args.baud} baud)"
    print(f"Connected to: {trans_desc}")

    active_mode = args.mode.upper()  # "DYNAMIC" or "PREDEFINED"
    bank_idx = 0
    render_board(active_mode, spec_mgr, bank_idx)

    current_command = "stop"
    last_keepalive_time = 0.0
    last_folder_check = time.time()

    try:
        while True:
            poller.update()
            now = time.time()

            # Live watch: check if specs/ folder changed every 2.0 seconds
            if now - last_folder_check >= 2.0:
                last_folder_check = now
                if spec_mgr.rescan():
                    print("\n[Folder Update] Detected changes in specs/. Updating Dynamic Library...")
                    if active_mode == "DYNAMIC":
                        render_board(active_mode, spec_mgr, bank_idx)

            # Check for Exit
            if poller.is_down('ESCAPE'):
                print("\n[Exit] Escape pressed. Shutting down...")
                break

            # -------------------------------------------------------------
            # Switch Libraries with TAB key
            # -------------------------------------------------------------
            if poller.just_pressed('TAB'):
                active_mode = "PREDEFINED" if active_mode == "DYNAMIC" else "DYNAMIC"
                spec_mgr.rescan(force=True)
                render_board(active_mode, spec_mgr, bank_idx)
                time.sleep(0.1)
                continue

            # -------------------------------------------------------------
            # Bank Pagination in Dynamic Mode ('[' and ']')
            # -------------------------------------------------------------
            if active_mode == "DYNAMIC":
                per_page = len(SLOT_KEYS)
                total_banks = max(1, (len(spec_mgr.specs) + per_page - 1) // per_page)
                if poller.just_pressed('LBRACKET'):
                    bank_idx = (bank_idx - 1) % total_banks
                    render_board(active_mode, spec_mgr, bank_idx)
                    continue
                elif poller.just_pressed('RBRACKET'):
                    bank_idx = (bank_idx + 1) % total_banks
                    render_board(active_mode, spec_mgr, bank_idx)
                    continue

            # -------------------------------------------------------------
            # Directional Locomotion Keys (WASD + Diagonals + Strafes)
            # -------------------------------------------------------------
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

            if desired_move is not None:
                should_send = False
                if desired_move != current_command:
                    should_send = True
                    print(f"\rStatus: >> [{cmd_char.upper()}] {desired_move:<14} | Lib: {active_mode:<10}", end="", flush=True)
                elif (now - last_keepalive_time >= 0.05):
                    should_send = True

                if should_send:
                    current_command = desired_move
                    last_keepalive_time = now
                    robot.send_command(current_command)
            else:
                # Movement key released -> auto-stop
                if current_command in ["run", "back", "turnL", "turnR", "upLeft", "upRight", 
                                       "backLeft", "backRight", "strafeLeft", "strafeRight"]:
                    current_command = "stop"
                    robot.send_command("stop")
                    print(f"\rStatus: .. [ ] STOPPED        | Lib: {active_mode:<10}", end="", flush=True)

                # ---------------------------------------------------------
                # Action Keys: Dynamic MoveSpecs vs Predefined Tricks
                # ---------------------------------------------------------
                if active_mode == "DYNAMIC":
                    per_page = len(SLOT_KEYS)
                    start_idx = bank_idx * per_page
                    bank_specs = spec_mgr.specs[start_idx : start_idx + per_page]

                    for idx, key in enumerate(SLOT_KEYS):
                        if idx < len(bank_specs) and poller.just_pressed(key):
                            spec = bank_specs[idx]
                            print(f"\nStatus: >> [SPEC] Activating '{spec['name']}' ({spec['filename']})...")
                            robot.send_command("stop")
                            time.sleep(0.08)
                            robot.send_spec(spec['data'])
                            current_command = f"spec:{spec['name']}"
                            break

                else:  # PREDEFINED MODE
                    for key, cmd in PREDEFINED_MAP.items():
                        if poller.just_pressed(key):
                            print(f"\rStatus: ** [!] {cmd:<14} | Lib: PREDEFINED", end="", flush=True)
                            robot.send_command(cmd)
                            current_command = cmd
                            break

            time.sleep(0.02)  # 50 Hz poll rate

    except KeyboardInterrupt:
        print("\n[Exit] Interrupted by user.")
    finally:
        print("\nStopping robot and cleaning up...")
        if robot:
            robot.send_command("stop")
            robot.close()
        print("Done. Goodbye!")


if __name__ == "__main__":
    main()
