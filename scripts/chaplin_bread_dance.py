#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925)
Recreates the iconic tabletop bread roll dance using FairyKame's front legs
as the two bread rolls on forks, while the rear haunches remain seated.
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

# Stable seated haunches base
HAUNCHES_BASE = {
    "bl": [45, -20],
    "br": [45, -20],
}

def run_bread_dance():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 60)
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (THE GOLD RUSH)  ")
    print("=" * 60)

    # Act 1: Curtain Rises / Bread Rolls on Table
    print("\n[Act 1/6] The Curtain Rises: Placing the Bread Rolls on the Table (2.5s)...")
    print("-> Chaplin perches his chin on his hands, smiling at the dinner table.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "breadDanceSetup",
        "fl": [30, 10],
        "fr": [30, 10],
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
        "fl": {"mode": "flex", "period": 320, "amplitude": 24, "phase": 0, "spread": 30, "height": 15},
        "fr": {"mode": "flex", "period": 320, "amplitude": 24, "phase": 180, "spread": 30, "height": 15},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(tap_spec)
    time.sleep(7.0)

    # Act 3: The High-Kicking Can-Can
    print("\n[Act 3/6] The High-Kicking Can-Can (7s)...")
    print("-> Exaggerated high kicks kicking up into the air and down to the table!")
    kick_spec = {
        "name": "breadDanceKicks",
        "fl": {"mode": "flex", "period": 550, "amplitude": 38, "phase": 0, "spread": 26, "height": 22},
        "fr": {"mode": "flex", "period": 550, "amplitude": 38, "phase": 180, "spread": 26, "height": 22},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(kick_spec)
    time.sleep(7.0)

    # Act 4: The Twinkle-Toes Synchronized Sway
    print("\n[Act 4/6] The Twinkle-Toes Synchronized Sway (7s)...")
    print("-> Both bread rolls sliding and swaying side-to-side in parallel unison.")
    sway_spec = {
        "name": "breadDanceSway",
        "fl": {
            "mode": "walk",
            "period": 500,
            "ampSpread": 20,
            "ampHeight": 14,
            "phase": 0,
            "spread": 30,
            "height": 12,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 500,
            "ampSpread": 20,
            "ampHeight": 14,
            "phase": 180,
            "spread": 30,
            "height": 12,
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
    print("-> Full 2-DOF rolling circular footwork across the tabletop.")
    waltz_spec = {
        "name": "breadDanceWaltz",
        "fl": {
            "mode": "walk",
            "period": 650,
            "ampSpread": 18,
            "ampHeight": 26,
            "phase": 0,
            "spread": 32,
            "height": 14,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 650,
            "ampSpread": 18,
            "ampHeight": 26,
            "phase": 180,
            "spread": 32,
            "height": 14,
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
    print("-> Paws dip into a dramatic Chaplin bow as the audience applauds!")
    bow_spec = {
        "name": "breadDanceBow",
        "fl": [38, 45],
        "fr": [18, 45],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(3.5)

    # Easing into rest
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's Bread Dance is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
