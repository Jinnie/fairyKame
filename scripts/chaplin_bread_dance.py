#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925) - Version 1.0
- Peak towering stilt elevation (rear height = -78, spread = 2)
- Front legs clenched parallel together in front (spread = 84, close feet like shoes on forks)
- Crisp, short theatrical curtsy bow (1.5s)
- 6-act performance tuned to perfection
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

# Peak towering rear stilt base (straight down vertical stilts)
HAUNCHES_BASE = {
    "bl": [2, -78],
    "br": [2, -78],
}

def run_bread_dance():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 65)
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (v1.0 DEFINITIVE)  ")
    print("=" * 65)

    # Act 1: Curtain Rises / High Stilt Setup
    print("\n[Act 1/6] The Curtain Rises: Peak Stilt Stance (2.0s)...")
    print("-> Max vertical stilt height, paws clenched parallel together in front.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "breadDanceSetupV1",
        "fl": [84, -45],
        "fr": [84, -45],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_spec(setup_spec)
    time.sleep(2.0)

    # Act 2: Ultra-Tight Rapid Pitter-Patter Tap Shuffle
    print("\n[Act 2/6] Rapid Pitter-Patter Tap Shuffle (7s)...")
    print("-> Snappy alternating heel-and-toe tabletop taps (270ms tempo).")
    tap_spec = {
        "name": "breadDanceTapV1",
        "fl": {"mode": "flex", "period": 270, "amplitude": 28, "phase": 0, "spread": 84, "height": -40},
        "fr": {"mode": "flex", "period": 270, "amplitude": 28, "phase": 180, "spread": 84, "height": -40},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(tap_spec)
    time.sleep(7.0)

    # Act 3: Sky-High Stilt Can-Can Kicks
    print("\n[Act 3/6] Sky-High Stilt Can-Can Kicks (7s)...")
    print("-> Huge theatrical kicks swinging high into the air and snapping down!")
    kick_spec = {
        "name": "breadDanceKicksV1",
        "fl": {"mode": "flex", "period": 480, "amplitude": 48, "phase": 0, "spread": 80, "height": -20},
        "fr": {"mode": "flex", "period": 480, "amplitude": 48, "phase": 180, "spread": 80, "height": -20},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(kick_spec)
    time.sleep(7.0)

    # Act 4: Tight Twinkle-Toes Synchronized Shimmy
    print("\n[Act 4/6] Tight Twinkle-Toes Shimmy (7s)...")
    print("-> Both feet sliding and swaying side-to-side in tight parallel lockstep.")
    sway_spec = {
        "name": "breadDanceSwayV1",
        "fl": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 6,
            "ampHeight": 18,
            "phase": 0,
            "spread": 84,
            "height": -42,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 6,
            "ampHeight": 18,
            "phase": 180,
            "spread": 84,
            "height": -42,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(sway_spec)
    time.sleep(7.0)

    # Act 5: Vertical Bread Roll Waltz
    print("\n[Act 5/6] Vertical Bread Roll Waltz (7s)...")
    print("-> 2-DOF rolling circular footwork in parallel forward sync.")
    waltz_spec = {
        "name": "breadDanceWaltzV1",
        "fl": {
            "mode": "walk",
            "period": 520,
            "ampSpread": 8,
            "ampHeight": 28,
            "phase": 0,
            "spread": 84,
            "height": -40,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 520,
            "ampSpread": 8,
            "ampHeight": 28,
            "phase": 180,
            "spread": 84,
            "height": -40,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(waltz_spec)
    time.sleep(7.0)

    # Act 6: Crisp Theatrical Curtsy Bow & Applause
    print("\n[Act 6/6] Crisp Theatrical Curtsy Bow (1.5s)...")
    print("-> Quick, crisp bow dip and release!")
    bow_spec = {
        "name": "breadDanceBowV1",
        "fl": [86, 5],
        "fr": [74, 5],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(1.5)

    # Easing into rest
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's Bread Dance v1.0 is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
