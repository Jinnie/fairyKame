#!/usr/bin/env python3
"""
FairyKame 15-Second Robotic Can-Can Practice
Recreates Chaplin's iconic high-leg freeze and jiggle from The Gold Rush:
1. Right leg pulled aaaaallll the way UP (held sky-high) while left leg jiggles on table (5s)
2. Left leg pulled aaaaallll the way UP (held sky-high) while right leg jiggles on table (5s)
3. Full alternating sky-high Can-Can kick frenzy (5s)
"""

import sys
import os
import time

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

from bridge.transport import get_transport

# Stable towering rear base
HAUNCHES_BASE = {
    "bl": [5, -70],
    "br": [5, -70],
}

def run_can_can():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 60)
    print("  CHARLIE CHAPLIN'S 15-SECOND ROBOTIC CAN-CAN PRACTICE  ")
    print("=" * 60)

    # Move 1: Right Leg Sky-High Hold + Left Leg Jiggle (5s)
    print("\n[Can-Can 1/3] Right Leg Aaaaallll the Way UP! Left Leg Jiggling (5s)...")
    print("-> Right paw points sky-high; left paw taps fast on the tabletop.")
    spec_right_high = {
        "name": "canCanRightHigh",
        "fl": {
            "mode": "flex",
            "period": 240,
            "amplitude": 24,
            "phase": 0,
            "spread": 78,
            "height": -35
        },
        "fr": [78, 68],  # held high in the sky!
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_right_high)
    time.sleep(5.0)

    # Move 2: Left Leg Sky-High Hold + Right Leg Jiggle (5s)
    print("\n[Can-Can 2/3] Left Leg Aaaaallll the Way UP! Right Leg Jiggling (5s)...")
    print("-> Left paw points sky-high; right paw taps fast on the tabletop.")
    spec_left_high = {
        "name": "canCanLeftHigh",
        "fl": [78, 68],  # held high in the sky!
        "fr": {
            "mode": "flex",
            "period": 240,
            "amplitude": 24,
            "phase": 0,
            "spread": 78,
            "height": -35
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_left_high)
    time.sleep(5.0)

    # Move 3: Alternating Sky-High Can-Can Frenzy (5s)
    print("\n[Can-Can 3/3] Alternating Sky-High Can-Can Frenzy (5s)...")
    print("-> Both legs kicking straight up to the sky and stomping down in rapid frenzy!")
    spec_frenzy = {
        "name": "canCanFrenzy",
        "fl": {
            "mode": "flex",
            "period": 380,
            "amplitude": 50,
            "phase": 0,
            "spread": 76,
            "height": -10
        },
        "fr": {
            "mode": "flex",
            "period": 380,
            "amplitude": 50,
            "phase": 180,
            "spread": 76,
            "height": -10
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_frenzy)
    time.sleep(5.0)

    # Gentle stop
    robot.send_command("stop")
    print("\nBravo! Robotic Can-Can Practice is complete!\n")

if __name__ == "__main__":
    run_can_can()
