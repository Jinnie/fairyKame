#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925)
Recreates the iconic tabletop bread roll dance:
- Elevated tiptoe stance (tall body, not a low crouching spider)
- Front legs held close together directly in front (like two little human feet on forks)
- 6-act performance 1:1 with the original tempo and moves
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

# Elevated, narrow tiptoe rear base (tall stance, not a wide spider splay)
HAUNCHES_BASE = {
    "bl": [20, -40],
    "br": [20, -40],
}

def run_bread_dance():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 60)
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (TIPTOE EDITION)  ")
    print("=" * 60)

    # Act 1: Curtain Rises / Feet on Table
    print("\n[Act 1/6] The Curtain Rises: Feet on Table in Front (2.5s)...")
    print("-> High tiptoe stance, paws held close and forward like little shoes.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "breadDanceSetup",
        "fl": [55, -15],
        "fr": [55, -15],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_spec(setup_spec)
    time.sleep(2.5)

    # Act 2: The Rapid Pitter-Patter Tap Shuffle
    print("\n[Act 2/6] The Pitter-Patter Tap Shuffle (7s)...")
    print("-> Fast, snappy alternating heel-and-toe tabletop taps (320ms tempo).")
    tap_spec = {
        "name": "breadDanceTap",
        "fl": {"mode": "flex", "period": 320, "amplitude": 24, "phase": 0, "spread": 55, "height": -10},
        "fr": {"mode": "flex", "period": 320, "amplitude": 24, "phase": 180, "spread": 55, "height": -10},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(tap_spec)
    time.sleep(7.0)

    # Act 3: The High-Kicking Can-Can
    print("\n[Act 3/6] The High-Kicking Can-Can (7s)...")
    print("-> Exaggerated alternating high kicks kicking straight up in front!")
    kick_spec = {
        "name": "breadDanceKicks",
        "fl": {"mode": "flex", "period": 550, "amplitude": 36, "phase": 0, "spread": 50, "height": 5},
        "fr": {"mode": "flex", "period": 550, "amplitude": 36, "phase": 180, "spread": 50, "height": 5},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(kick_spec)
    time.sleep(7.0)

    # Act 4: The Twinkle-Toes Synchronized Sway
    print("\n[Act 4/6] The Twinkle-Toes Synchronized Sway (7s)...")
    print("-> Both feet sliding and swaying side-to-side in front in parallel unison.")
    sway_spec = {
        "name": "breadDanceSway",
        "fl": {
            "mode": "walk",
            "period": 500,
            "ampSpread": 15,
            "ampHeight": 14,
            "phase": 0,
            "spread": 55,
            "height": -12,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 500,
            "ampSpread": 15,
            "ampHeight": 14,
            "phase": 180,
            "spread": 55,
            "height": -12,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(sway_spec)
    time.sleep(7.0)

    # Act 5: The Grand Circular Bread Roll Waltz
    print("\n[Act 5/6] The Grand Circular Waltz (7s)...")
    print("-> Full 2-DOF rolling circular footwork in front across the tabletop.")
    waltz_spec = {
        "name": "breadDanceWaltz",
        "fl": {
            "mode": "walk",
            "period": 650,
            "ampSpread": 15,
            "ampHeight": 24,
            "phase": 0,
            "spread": 55,
            "height": -10,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 650,
            "ampSpread": 15,
            "ampHeight": 24,
            "phase": 180,
            "spread": 55,
            "height": -10,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(waltz_spec)
    time.sleep(7.0)

    # Act 6: The Theatrical Curtsy Bow & Applause
    print("\n[Act 6/6] The Theatrical Grand Bow & Curtsy (3.5s)...")
    print("-> Paws cross in front and dip into a dramatic Chaplin bow!")
    bow_spec = {
        "name": "breadDanceBow",
        "fl": [60, 20],
        "fr": [45, 20],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(3.5)

    # Easing into rest
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's Tiptoe Bread Dance is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
