#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925) - Authentic 2-DOF Edition
Recreates the true silent-film fork choreography:
- Act 1: Towering stilt curtain rise & setup
- Act 2: The "Charleston" In-and-Out Splay & Knock-Knees (symmetrical hip opening & closing)
- Act 3: The "Tabletop Stroll" (alternating forward/backward walking forks)
- Act 4: The "Comical Split & Snap" (slow slide into wide split, pause, and SNAP shut!)
- Act 5: The "Scissors Crossover" (figure-8 twinkle-toe shuffle)
- Act 6: Crisp Theatrical Curtsy Bow (1.5s)
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
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (2-DOF AUTHENTIC)  ")
    print("=" * 65)

    # Act 1: Curtain Rises / Towering Setup
    print("\n[Act 1/6] The Curtain Rises: Towering Stilt Stance (2.0s)...")
    print("-> Chaplin sits tall, forks resting parallel in front of his chest.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "chaplinSetup",
        "fl": [82, -42],
        "fr": [82, -42],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_spec(setup_spec)
    time.sleep(2.0)

    # Act 2: The "Charleston" In-and-Out Splay & Knock-Knees
    print("\n[Act 2/6] The 'Charleston' In-and-Out Splay & Knock-Knees (7.0s)...")
    print("-> Both hips swinging symmetrically in and out while tapping the tabletop!")
    # Same phase (0 on both) causes both legs to splay outward together and snap inward together
    charleston_spec = {
        "name": "chaplinCharleston",
        "fl": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 18,
            "ampHeight": 22,
            "phase": 0,
            "spread": 68,
            "height": -38,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 18,
            "ampHeight": 22,
            "phase": 0,
            "spread": 68,
            "height": -38,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(charleston_spec)
    time.sleep(7.0)

    # Act 3: The "Tabletop Stroll" - Walking Forks
    print("\n[Act 3/6] The 'Tabletop Stroll' - Walking Forks (7.0s)...")
    print("-> One fork steps forward while the other steps back, walking across the table!")
    # 180 phase difference causes alternating forward/backward stride
    stroll_spec = {
        "name": "chaplinStroll",
        "fl": {
            "mode": "walk",
            "period": 480,
            "ampSpread": 18,
            "ampHeight": 28,
            "phase": 0,
            "spread": 70,
            "height": -38,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 480,
            "ampSpread": 18,
            "ampHeight": 28,
            "phase": 180,
            "spread": 70,
            "height": -38,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(stroll_spec)
    time.sleep(7.0)

    # Act 4: The Comical Split & Snap
    print("\n[Act 4/6] The Comical Split & Snap (3.5s)...")
    print("-> Slow slide into a wide split on the tablecloth... freeze... and SNAP shut!")
    # Part A: Slide into wide split (2.0s)
    split_spec = {
        "name": "chaplinSplit",
        "fl": [42, -35],
        "fr": [42, -35],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(split_spec)
    time.sleep(2.0)
    # Part B: Fast snap shut (1.5s)
    snap_spec = {
        "name": "chaplinSnap",
        "fl": [84, -45],
        "fr": [84, -45],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_spec(snap_spec)
    time.sleep(1.5)

    # Act 5: The "Scissors Crossover" Twinkle-Toe Shuffle
    print("\n[Act 5/6] The 'Scissors Crossover' Twinkle-Toe Shuffle (7.0s)...")
    print("-> Paws crossing over each other in an intricate figure-8 shuffle!")
    scissors_spec = {
        "name": "chaplinScissors",
        "fl": {
            "mode": "walk",
            "period": 460,
            "ampSpread": 14,
            "ampHeight": 22,
            "phase": 0,
            "spread": 76,
            "height": -38,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 460,
            "ampSpread": 14,
            "ampHeight": 22,
            "phase": 90,
            "spread": 76,
            "height": -38,
            "direction": "forward"
        },
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(scissors_spec)
    time.sleep(7.0)

    # Act 6: Crisp Theatrical Curtsy Bow & Applause
    print("\n[Act 6/6] Crisp Theatrical Curtsy Bow (1.5s)...")
    print("-> Quick bow dip and freeze for applause!")
    bow_spec = {
        "name": "chaplinBow",
        "fl": [86, 5],
        "fr": [74, 5],
        "bl": HAUNCHES_BASE["bl"],
        "br": HAUNCHES_BASE["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(1.5)

    # Complete rest
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's 2-DOF Bread Dance is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
