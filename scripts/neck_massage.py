#!/usr/bin/env python3
"""
FairyKame Neck & Shoulder Massage Controller

Mount FairyKame on your upper back / between shoulder blades facing your neck.
The rear legs act as an ultra-wide flat anchor kickstand for rock-solid stability,
while the front paws perform rhythmic massaging sequences.

Usage:
    python scripts/neck_massage.py --mount       # Adopt wide, flat mounting pose to place robot on your back
    python scripts/neck_massage.py --session     # Run full multi-stage spa massage session (tap + knead)
    python scripts/neck_massage.py --knead       # Continuous alternating deep circular knead
    python scripts/neck_massage.py --tap         # Continuous gentle shiatsu acupressure tapping
    python scripts/neck_massage.py --stop        # Emergency stop / relax
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

# Mount / Anchor Pose
MOUNT_SPEC = {
    "name": "massageMount",
    "description": "Flat, wide kickstand posture for mounting on upper back",
    "fl": [42, 45],
    "fr": [42, 45],
    "bl": [45, -20],
    "br": [45, -20]
}

def load_spec_file(filename: str):
    path = os.path.join(PROJECT_ROOT, "specs", filename)
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

def run_massage_session(robot, duration_scale: float = 1.0):
    print("\n" + "=" * 50)
    print("  FAIRYKAME SPA & WELLNESS: NECK MASSAGE SESSION  ")
    print("=" * 50)
    
    # Stage 1: Stabilizing Mount
    print("\n[Stage 1/4] Establishing Base Anchor Kickstand (3s)...")
    print("-> Splaying rear legs wide and flat; resting belly onto back.")
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(MOUNT_SPEC)
    time.sleep(3.0 * duration_scale)

    # Stage 2: Deep Shiatsu Acupressure Tap
    print("\n[Stage 2/4] Deep Shiatsu Acupressure Tapping (20s)...")
    print("-> Firm, rhythmic vertical drumming on trapezius muscles.")
    tap_spec = load_spec_file("neck_massage_tap.json")
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(tap_spec)
    time.sleep(20.0 * duration_scale)

    # Stage 3: Alternating Deep Circular Knead
    print("\n[Stage 3/4] Alternating Deep Circular Kneading (30s)...")
    print("-> Deep, rolling 2-DOF circular paws working neck and shoulders.")
    knead_spec = load_spec_file("neck_massage.json")
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(knead_spec)
    time.sleep(30.0 * duration_scale)

    # Stage 4: Gentle Finish & Relax
    print("\n[Stage 4/4] Massage Complete! Easing into resting pose...")
    robot.send_spec(MOUNT_SPEC)
    time.sleep(1.5)
    robot.send_command("stop")
    print("-> FairyKame relaxed. Hope your neck feels great!\n")

def main():
    parser = argparse.ArgumentParser(description="FairyKame Neck Massage Controller")
    parser.add_argument("--mount", action="store_true", help="Set wide, flat mounting pose to position robot on back")
    parser.add_argument("--session", action="store_true", help="Execute complete multi-stage spa massage session")
    parser.add_argument("--knead", action="store_true", help="Run alternating circular knead routine")
    parser.add_argument("--tap", action="store_true", help="Run rapid gentle shiatsu tap routine")
    parser.add_argument("--duration", "-d", type=float, default=None, help="Duration in seconds (for --knead or --tap)")
    parser.add_argument("--stop", "-s", action="store_true", help="Stop and relax immediately")
    parser.add_argument("--transport", "-t", choices=["auto", "wifi", "serial"], default="auto", help="Transport mode")
    parser.add_argument("--port", "-p", default=None, help="Serial port (if using USB)")

    args = parser.parse_args()

    print(f"Connecting to FairyKame ({args.transport})...")
    robot = get_transport(mode=args.transport, serial_port=args.port)

    if args.stop:
        print("Stopping FairyKame...")
        ok = robot.send_command("stop")
        print("Stop:", "OK" if ok else "FAILED")
        return 0 if ok else 1

    if args.mount:
        print("Adopting wide, flat mounting posture...")
        robot.send_command("stop")
        time.sleep(0.15)
        ok = robot.send_spec(MOUNT_SPEC)
        print("Mount posture ready! Place FairyKame on your upper back.")
        return 0 if ok else 1

    if args.session:
        run_massage_session(robot)
        return 0

    if args.knead:
        spec = load_spec_file("neck_massage.json")
        name = spec.get("name", "neckMassage")
        robot.send_command("stop")
        time.sleep(0.15)
        if args.duration and args.duration > 0:
            print(f"Running '{name}' for {args.duration:.1f}s...")
            robot.send_spec(spec)
            time.sleep(args.duration)
            robot.send_command("stop")
        else:
            print(f"Running '{name}' (continuous)...")
            robot.send_spec(spec)
        return 0

    if args.tap:
        spec = load_spec_file("neck_massage_tap.json")
        name = spec.get("name", "neckMassageTap")
        robot.send_command("stop")
        time.sleep(0.15)
        if args.duration and args.duration > 0:
            print(f"Running '{name}' for {args.duration:.1f}s...")
            robot.send_spec(spec)
            time.sleep(args.duration)
            robot.send_command("stop")
        else:
            print(f"Running '{name}' (continuous)...")
            robot.send_spec(spec)
        return 0

    # Default action if no flag specified: print help and show mount command
    parser.print_help()
    return 0

if __name__ == "__main__":
    sys.exit(main())
