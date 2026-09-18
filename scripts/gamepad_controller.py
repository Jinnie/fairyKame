#!/usr/bin/env python3
"""
FairyKame Gamepad Controller (Dynamic MoveSpec & Locomotion)
------------------------------------------------------------
Interactive, low-latency keyboard controller for FairyKame over USB Serial or Wi-Fi.

Features:
  - Dynamically reads all MoveSpecs (*.json) from specs/ and offers them in the UI.
  - Interactive MoveSpec Library Menu (press TAB or L) with arrow-key navigation.
  - Quick-action MoveSpec Hotbar (cycle with '[' and ']', play with ENTER or '\').
  - Low-latency hold-to-move WASD locomotion with instant release-to-stop.
  - Direct trick keys (0-9, P, K, H, R, M) and emergency stop (Space).
  - Dual transport support: Auto-detects USB Serial or local Wi-Fi (http://fairy.local).
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
                'UP': 0x26, 'DOWN': 0x28, 'LEFT': 0x25, 'RIGHT': 0x27,
                'LBRACKET': 0xDB, 'RBRACKET': 0xDD, 'BACKSLASH': 0xDC,
                'L': 0x4C, 'M': 0x4D, 'P': 0x50, 'K': 0x4B, 'H': 0x48, 'R': 0x52,
                '0': 0x30, '1': 0x31, '2': 0x32, '3': 0x33, '4': 0x34,
                '5': 0x35, '6': 0x36, '7': 0x37, '8': 0x38, '9': 0x39
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


def load_specs(specs_dir: str):
    """Dynamically reads all valid MoveSpec JSON files from specs directory."""
    specs = []
    if not os.path.exists(specs_dir):
        return specs

    for fname in sorted(os.listdir(specs_dir)):
        if fname.endswith(".json") and fname != "calibration.json":
            fpath = os.path.join(specs_dir, fname)
            try:
                with open(fpath, "r", encoding="utf-8") as f:
                    data = json.load(f)
                if "fl" in data and "fr" in data:
                    name = data.get("name", os.path.splitext(fname)[0])
                    desc = data.get("description", "Dynamic MoveSpec").strip()
                    # Keep description concise for terminal display
                    desc_summary = desc.split("\n")[0]
                    if len(desc_summary) > 65:
                        desc_summary = desc_summary[:62] + "..."
                    specs.append({
                        "name": name,
                        "description": desc_summary,
                        "filename": fname,
                        "data": data
                    })
            except Exception:
                continue
    return specs


BANNER = r"""
  ___     _          _  __                  
 | __|_ _(_)_ _ _  _| |/ /__ _ _ __  ___    
 | _/ _` | | '_| || | ' </ _` | '  \/ -_)   
 |_|\__,_|_|_|  \_, |_|\_\__,_|_|_|_\___|   
                |__/                        
  >>> Computer-Game Keyboard Controller <<<
"""

HELP_TEXT = r"""
[ Locomotion ] (Hold to Move - Release to Stop Instantly)
    W / S          : Forward (Park Walk) / Backward
    A / D          : Turn Left / Turn Right
    W+A / W+D      : Diagonal Up-Left / Up-Right
    S+A / S+D      : Diagonal Down-Left / Down-Right
    Q / E          : Dedicated Diagonal Up-Left / Up-Right
    Z / C          : Dedicated Diagonal Down-Left / Down-Right
    < , > / < . >  : Strafe Left (,) / Strafe Right (.)

[ MoveSpec Library & Hotbar ]
    [ / ]          : Select Previous / Next MoveSpec in Hotbar
    ENTER or \     : Execute Currently Selected Hotbar MoveSpec
    TAB or L       : Toggle Interactive MoveSpec Library Menu
    SPACE          : Stop Robot & Zero Torques

[ Baked-in Tricks & Poses ] (Tap Key)
    1: Dance       2: Push Ups    3: Sit         4: Crawl
    5: Tiptoe      6 / H: Say Hi  7: Tap Foot    8: Play Dead
    9: Shiver      0: Pack        P: Pounce      K: Scratch Ear
    R: Recover     M: Magic
"""


def render_menu(specs, selected_idx):
    """Renders the interactive full-screen MoveSpec selection menu."""
    print("\n" + "=" * 80)
    print("===                    FAIRYKAME MOVESPEC LIBRARY                            ===")
    print("=" * 80)
    for i, item in enumerate(specs):
        marker = ">>" if i == selected_idx else "  "
        print(f" {marker} [{i + 1:2d}] {item['name']:<18} : {item['description']}")
    print("-" * 80)
    print(" [UP / DOWN] Navigate | [ENTER] Play Spec | [SPACE] Stop | [TAB / ESC] Resume WASD")
    print("=" * 80 + "\n")


def main():
    parser = argparse.ArgumentParser(description="FairyKame Gamepad Controller with Dynamic MoveSpec Library")
    parser.add_argument("--transport", "-t", choices=["auto", "wifi", "serial"], default="auto", help="Transport mode (default: auto)")
    parser.add_argument("--port", "-p", default=None, help="Serial COM port (default: auto-detected, e.g. COM6)")
    parser.add_argument("--baud", "-b", type=int, default=115200, help="Serial baud rate (default: 115200)")
    parser.add_argument("--url", default="http://fairy.local", help="Wi-Fi base URL (default: http://fairy.local)")
    args = parser.parse_args()

    # Load dynamic MoveSpecs
    specs_dir = os.path.join(PROJECT_ROOT, "specs")
    specs = load_specs(specs_dir)

    print(f"Connecting to FairyKame ({args.transport})...")
    try:
        robot = get_transport(mode=args.transport, base_url=args.url, serial_port=args.port, baudrate=args.baud)
    except Exception as e:
        print(f"[Error] Failed to connect to robot: {e}")
        sys.exit(1)

    # Optional background drain thread if serial
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
    print(f"MoveSpecs Loaded: {len(specs)} dynamic specifications from specs/")
    print(HELP_TEXT)
    print("Controller is ACTIVE. Start pressing WASD / keys...\n")

    current_command = "stop"
    last_trick_key = None
    last_keepalive_time = 0.0
    hotbar_idx = 0
    menu_mode = False
    menu_cursor = 0

    try:
        while True:
            poller.update()

            # -------------------------------------------------------------
            # Interactive MoveSpec Menu Mode (TAB / L)
            # -------------------------------------------------------------
            if menu_mode:
                if poller.just_pressed('ESCAPE') or poller.just_pressed('TAB'):
                    menu_mode = False
                    print("\n[Menu Closed] Returning to standard WASD free-roam mode.")
                    time.sleep(0.1)
                    continue

                if poller.just_pressed('UP'):
                    menu_cursor = (menu_cursor - 1) % len(specs)
                    render_menu(specs, menu_cursor)

                elif poller.just_pressed('DOWN'):
                    menu_cursor = (menu_cursor + 1) % len(specs)
                    render_menu(specs, menu_cursor)

                elif poller.just_pressed('RETURN'):
                    selected = specs[menu_cursor]
                    hotbar_idx = menu_cursor
                    print(f"\n[Spec Activated] Transmitting MoveSpec '{selected['name']}'...")
                    robot.send_command("stop")
                    time.sleep(0.1)
                    robot.send_spec(selected['data'])
                    current_command = f"spec:{selected['name']}"
                    menu_mode = False
                    print(f"[Menu Closed] Playing '{selected['name']}'. Press SPACE to stop or WASD to steer.")
                    time.sleep(0.1)
                    continue

                elif poller.just_pressed('SPACE'):
                    robot.send_command("stop")
                    current_command = "stop"
                    print("\n[Stop] Robot relaxed.")

                time.sleep(0.02)
                continue

            # -------------------------------------------------------------
            # Standard Controller Mode (WASD & Hotbar)
            # -------------------------------------------------------------

            # Check for Menu toggle (TAB or L)
            if poller.just_pressed('TAB') or poller.just_pressed('L'):
                menu_mode = True
                menu_cursor = hotbar_idx
                render_menu(specs, menu_cursor)
                time.sleep(0.1)
                continue

            # Check for Exit
            if poller.is_down('ESCAPE'):
                print("\n[Exit] Escape pressed. Shutting down...")
                break

            # Hotbar navigation ('[' and ']')
            if specs:
                if poller.just_pressed('LBRACKET'):
                    hotbar_idx = (hotbar_idx - 1) % len(specs)
                    s = specs[hotbar_idx]
                    print(f"\rHotbar: << [{hotbar_idx + 1:2d}/{len(specs)}] {s['name']:<18} : {s['description']}", end="", flush=True)

                elif poller.just_pressed('RBRACKET'):
                    hotbar_idx = (hotbar_idx + 1) % len(specs)
                    s = specs[hotbar_idx]
                    print(f"\rHotbar: >> [{hotbar_idx + 1:2d}/{len(specs)}] {s['name']:<18} : {s['description']}", end="", flush=True)

                # Execute Hotbar MoveSpec (ENTER or BACKSLASH)
                if poller.just_pressed('RETURN') or poller.just_pressed('BACKSLASH'):
                    s = specs[hotbar_idx]
                    print(f"\n\rStatus: >> [SPEC] Activating '{s['name']}'...                 ", end="", flush=True)
                    robot.send_command("stop")
                    time.sleep(0.1)
                    robot.send_spec(s['data'])
                    current_command = f"spec:{s['name']}"
                    continue

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
                    current_spec_tag = specs[hotbar_idx]['name'] if specs else "None"
                    print(f"\rStatus: >> [{cmd_char.upper()}] {desired_move:<14} | Hotbar: [{hotbar_idx + 1:2d}] {current_spec_tag:<16}", end="", flush=True)
                elif (now - last_keepalive_time >= 0.05):
                    # Stream keepalive pulses every 50ms to satisfy firmware watchdog while held
                    should_send = True

                if should_send:
                    current_command = desired_move
                    last_keepalive_time = now
                    robot.send_command(current_command)
            else:
                # No movement key pressed
                if current_command in ["run", "back", "turnL", "turnR", "upLeft", "upRight", 
                                       "backLeft", "backRight", "strafeLeft", "strafeRight"]:
                    # Movement key released -> stop immediately
                    current_command = "stop"
                    robot.send_command("stop")
                    current_spec_tag = specs[hotbar_idx]['name'] if specs else "None"
                    print(f"\rStatus: .. [ ] STOPPED        | Hotbar: [{hotbar_idx + 1:2d}] {current_spec_tag:<16}", end="", flush=True)

                # Check one-shot trick keys
                trick_map = {
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

                pressed_trick = None
                for key_name, trick_cmd in trick_map.items():
                    if poller.is_down(key_name):
                        pressed_trick = trick_cmd
                        break

                if pressed_trick and pressed_trick != last_trick_key:
                    current_command = pressed_trick
                    robot.send_command(pressed_trick)
                    print(f"\rStatus: ** [!] {pressed_trick:<14} | Hotbar: [{hotbar_idx + 1:2d}] {specs[hotbar_idx]['name']:<16}", end="", flush=True)
                    last_trick_key = pressed_trick
                elif not pressed_trick:
                    last_trick_key = None

            time.sleep(0.02)  # 50 Hz loop

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
