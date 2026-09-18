#!/usr/bin/env python3
"""
Charlie Chaplin "Bread Dance" Choreography (The Gold Rush, 1925) - Definitive Edition
Dedicated to Ivan & Iva.
Fully adapted to FairyKame's calibrated physical boundaries:
- Act 1: The Grand Stilt Rise & Table Greeting (bl/br = [0, -90] true vertical stilts)
- Act 2: The Authentic 1925 Charleston In-and-Out Swivel (symmetrical hip splay 40 to 90 deg)
- Act 3: The TRUE 90-Degree Sky-High Can-Can Spectacle (+90 deg sky freezes & alternating frenzy)
- Act 4: The Tabletop Stroll / Parisian Promenade (alternating forward/back walking forks)
- Act 5: The Comical Slapstick Split & Snap (slow slide into wide split, pause, and SNAP!)
- Act 6: The Dedicated Curtsy Bow & Grand Finish
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

# Calibrated True Max Rear Stilts (-90 deg vertical straight legs)
CALIBRATED_STILTS = {
    "bl": [0, -90],
    "br": [0, -90],
}

def run_bread_dance():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")

    print("\n" + "=" * 65)
    print("  CHARLIE CHAPLIN'S 'BREAD ROLL DANCE' (DEFINITIVE EDITION)  ")
    print("=" * 65)

    # Act 1: The Grand Rise & Table Greeting (3.0s)
    print("\n[Act 1/6] The Grand Rise & Table Greeting (3.0s)...")
    print("-> FairyKame rises to 100% vertical stilt height, front paws placed parallel on the table.")
    robot.send_command("stop")
    time.sleep(0.15)
    setup_spec = {
        "name": "chaplinSetup",
        "fl": [88, -45],
        "fr": [88, -45],
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_spec(setup_spec)
    time.sleep(3.0)

    # Act 2: The Authentic 1925 Charleston Swivel & Knock-Knees (8.0s)
    print("\n[Act 2/6] The Authentic Charleston In-and-Out Swivel (8.0s)...")
    print("-> Full in-and-out hip splay (40 deg to 90 deg) with synchronized table tapping!")
    charleston_spec = {
        "name": "chaplinCharleston",
        "fl": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 24,
            "ampHeight": 26,
            "phase": 0,
            "spread": 66,
            "height": -45,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 420,
            "ampSpread": 24,
            "ampHeight": 26,
            "phase": 0,
            "spread": 66,
            "height": -45,
            "direction": "forward"
        },
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(charleston_spec)
    time.sleep(8.0)

    # Act 3: The TRUE 90-Degree Sky-High Can-Can Spectacle (9.0s)
    print("\n[Act 3/6] The TRUE 90-Degree Sky-High Can-Can Spectacle (9.0s)...")
    print("-> Right leg kicks all the way to the sky (+90 deg!), then left leg kicks (+90 deg!), then frenzy!")
    # Step A: Right leg straight up to +90 sky-freeze, left jiggling on table (3.0s)
    right_high_spec = {
        "name": "chaplinCanCanRight",
        "fl": {
            "mode": "flex",
            "period": 240,
            "amplitude": 25,
            "phase": 0,
            "spread": 86,
            "height": -45
        },
        "fr": [86, 90],  # TRUE CALIBRATED MAX SKY-HIGH (+90)!
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(right_high_spec)
    time.sleep(3.0)

    # Step B: Left leg straight up to +90 sky-freeze, right jiggling on table (3.0s)
    left_high_spec = {
        "name": "chaplinCanCanLeft",
        "fl": [86, 90],  # TRUE CALIBRATED MAX SKY-HIGH (+90)!
        "fr": {
            "mode": "flex",
            "period": 240,
            "amplitude": 25,
            "phase": 0,
            "spread": 86,
            "height": -45
        },
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(left_high_spec)
    time.sleep(3.0)

    # Step C: Alternating Full-Envelope High-Kick Frenzy (3.0s)
    frenzy_spec = {
        "name": "chaplinCanCanFrenzy",
        "fl": {
            "mode": "flex",
            "period": 360,
            "amplitude": 65,  # huge vertical swing from -65 to +65!
            "phase": 0,
            "spread": 82,
            "height": 0
        },
        "fr": {
            "mode": "flex",
            "period": 360,
            "amplitude": 65,
            "phase": 180,
            "spread": 82,
            "height": 0
        },
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(frenzy_spec)
    time.sleep(3.0)

    # Act 4: The Tabletop Stroll / Parisian Promenade (7.0s)
    print("\n[Act 4/6] The Tabletop Stroll / Parisian Promenade (7.0s)...")
    print("-> Alternating walking stride with high knee lifts across the tablecloth.")
    stroll_spec = {
        "name": "chaplinStroll",
        "fl": {
            "mode": "walk",
            "period": 460,
            "ampSpread": 20,
            "ampHeight": 32,
            "phase": 0,
            "spread": 70,
            "height": -40,
            "direction": "forward"
        },
        "fr": {
            "mode": "walk",
            "period": 460,
            "ampSpread": 20,
            "ampHeight": 32,
            "phase": 180,
            "spread": 70,
            "height": -40,
            "direction": "forward"
        },
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(stroll_spec)
    time.sleep(7.0)

    # Act 5: The Comical Slapstick Split & Snap (3.5s)
    print("\n[Act 5/6] The Comical Slapstick Split & Snap (3.5s)...")
    print("-> Slow comical slide into a wide split on the table... pause... and SNAP!")
    split_spec = {
        "name": "chaplinSplit",
        "fl": [35, -45],
        "fr": [35, -45],
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(split_spec)
    time.sleep(2.0)

    snap_spec = {
        "name": "chaplinSnap",
        "fl": [88, -50],
        "fr": [88, -50],
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_spec(snap_spec)
    time.sleep(1.5)

    # Act 6: Dedicated Curtsy Bow to Ivan & Iva (2.5s)
    print("\n[Act 6/6] Dedicated Curtsy Bow to Ivan & Iva (2.5s)...")
    print("-> Crossed paws dip into a graceful, theatrical Chaplin bow!")
    bow_spec = {
        "name": "chaplinBow",
        "fl": [88, 15],
        "fr": [70, 15],
        "bl": CALIBRATED_STILTS["bl"],
        "br": CALIBRATED_STILTS["br"]
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(bow_spec)
    time.sleep(2.5)

    # Grand Finish
    robot.send_command("stop")
    print("\nBravo! Charlie Chaplin's Definitive Bread Dance is complete!\n")

if __name__ == "__main__":
    run_bread_dance()
