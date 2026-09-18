#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925)
Ultra-Tall & Ultra-Tight Edition:
- Ultra-towering stilt elevation (rear height = -70, spread = 5)
- Front legs clenched ultra-tight together in front (spread = 78, touching parallel feet)
- 6-act performance dialed to the absolute limits of mechanical expression
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

# Ultra-towering rear stilt base
HAUNCHES_BASE = {
    "bl": [5, -70],
    "br": [5, -70],
}

def run_bread_dance():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 65)
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (ULTRA-TALL & TIGHT)  ")
    print("=" * 65)

    # Act 1: Curtain Rises / High Stilt Setup
    print("\n[Act 1/6] The Curtain Rises: Towering Stilt Stance (2.5s)...")
    print("-> Max vertical stilt height, paws clenched ultra-tight together in front.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "breadDanceSetupUltra",
        "fl": [78, -40],
        "fr": [78, -40],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_spec(setup_spec)
    time.sleep(2.5)

    # Act 2: Ultra-Tight Rapid Pitter-Patter Tap Shuffle
    print("\n[Act 2/6] Rapid Pitter-Patter Tap Shuffle (7s)...")
    print("-> Snappy alternating heel-and-toe tabletop taps (280ms tempo).")
    tap_spec = {
        "name": "breadDanceTapUltra",
        "fl": {"mode": "flex", "period": 280, "amplitude": 28, "phase": 0, "spread": 78, "height": -35},
        "fr": {"mode": "flex", "period": 280, "amplitude": 28, "phase": 180, "spread": 78, "height": -35},
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(tap_spec)
    time.sleep(7.0)

    # Act 3: Stilt Can-Can High Kicks
    print("\n[Act 3/6] Sky-High Stilt Can-Can Kicks (7s)...")
    print("-> Exaggerated high kicks kicking high into the air and snapping down!")
    kick_spec = {
        "name": "breadDanceKicksUltra",
        "fl": {"mode": "flex", "period": 500, "amplitude": 45, "phase": 0, "spread": 75, "height": -15},
        "fr": {"mode": "flex", "period": 500, "amplitude": 45, "phase": 180, "spread": 75, "height": -15},
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
        "name": "breadDanceSwayUltra",
        "fl": {
            "mode": "walk",
            "period": 450,
            "ampSpread": 8,
            "ampHeight": 18,
            "phase": 0,
            "spread": 78,
            "height": -36,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 450,
            "ampSpread": 8,
            "ampHeight": 18,
            "phase": 180,
            "spread": 78,
            "height": -36,
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
    print("-> 2-DOF rolling circular footwork in ultra-tight forward sync.")
    waltz_spec = {
        "name": "breadDanceWaltzUltra",
        "fl": {
            "mode": "walk",
            "period": 550,
            "ampSpread": 10,
            "ampHeight": 26,
            "phase": 0,
            "spread": 78,
            "height": -34,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 550,
            "ampSpread": 10,
            "ampHeight": 26,
            "phase": 180,
            "spread": 78,
            "height": -34,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(waltz_spec)
    time.sleep(7.0)

    # Act 6: Theatrical Grand Curtsy Bow & Applause
    print("\n[Act 6/6] Theatrical Grand Bow & Curtsy (3.5s)...")
    print("-> Paws cross tightly in front and dip down in a dramatic bow!")
    bow_spec = {
        "name": "breadDanceBowUltra",
        "fl": [82, 10],
        "fr": [68, 10],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(3.5)

    # Easing into rest
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's Ultra-Tall & Tight Bread Dance is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
