#!/usr/bin/env python3
"""
FairyKame MoveSpec Player
Transmits and plays MoveSpec JSON files on FairyKame over Wi-Fi or USB Serial.

Usage:
    python scripts/play_spec.py specs/atat_walker.json
    python scripts/play_spec.py specs/atat_walker.json --duration 10.0
    python scripts/play_spec.py --stop
"""

import sys
import os
import time
import json
import argparse

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from bridge.transport import get_transport

def main():
    parser = argparse.ArgumentParser(description="FairyKame MoveSpec Player")
    parser.add_argument("file", nargs="?", help="Path to MoveSpec JSON file to execute")
    parser.add_argument("--duration", "-d", type=float, default=None, help="Hold duration in seconds before stopping (default: hold continuously)")
    parser.add_argument("--stop", "-s", action="store_true", help="Send emergency stop and relax")
    parser.add_argument("--transport", "-t", choices=["auto", "wifi", "serial"], default="auto", help="Transport mode")
    parser.add_argument("--port", "-p", default=None, help="Serial port (e.g. COM6)")

    args = parser.parse_args()

    print(f"Connecting to FairyKame ({args.transport})...")
    robot = get_transport(mode=args.transport, serial_port=args.port)

    if args.stop:
        print("Stopping FairyKame...")
        ok = robot.send_command("stop")
        print("Stop:", "OK" if ok else "FAILED")
        return 0 if ok else 1

    if not args.file:
        parser.print_help()
        return 1

    if not os.path.exists(args.file):
        print(f"Error: File not found: {args.file}")
        return 1

    with open(args.file, "r", encoding="utf-8") as f:
        spec = json.load(f)

    name = spec.get("name", os.path.splitext(os.path.basename(args.file))[0])
    print(f"Loaded MoveSpec: '{name}' from {args.file}")

    # Momentary reset ensures main.cpp command dispatch executes cleanly
    robot.send_command("stop")
    time.sleep(0.15)

    if args.duration and args.duration > 0:
        print(f"Executing '{name}' for {args.duration:.1f}s...")
        ok = robot.send_spec(spec)
        if not ok:
            print("Failed to send MoveSpec to robot.")
            return 1
        time.sleep(args.duration)
        print("Stopping robot...")
        robot.send_command("stop")
    else:
        print(f"Activating '{name}' (continuous)...")
        ok = robot.send_spec(spec)
        if not ok:
            print("Failed to send MoveSpec to robot.")
            return 1

    print("Done!")
    return 0

if __name__ == "__main__":
    sys.exit(main())
