#!/usr/bin/env python3
"""
FairyKame Hind-Leg Waving Choreography
Waves the back-right (BR) leg in 4 distinct styles for 30 seconds
using both hip (spread) and knee (height) joints with an immovable 3-leg tripod base.
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

# Stable 3-leg ground tripod
TRIPOD_BASE = {
    "fl": [20, -25],
    "fr": [-20, -25],
    "bl": [45, -25],
}

def wave_hind_right():
    print("Connecting to FairyKame...")
    robot = get_transport("auto")
    
    print("\n" + "=" * 55)
    print("  FAIRYKAME 30-SECOND HIND-LEG (BR) WAVE SPECTACULAR  ")
    print("=" * 55)

    # Initial tripod anchor
    print("\n[Prep] Locking rock-solid 3-leg tripod anchor...")
    robot.send_command("stop")
    time.sleep(0.15)
    prep_spec = {
        "name": "tripodPrep",
        "fl": TRIPOD_BASE["fl"],
        "fr": TRIPOD_BASE["fr"],
        "bl": TRIPOD_BASE["bl"],
        "br": [45, 45]  # lift leg off ground
    }
    robot.send_spec(prep_spec)
    time.sleep(1.0)

    # Style 1: The Hip Wiper / Lateral Windshield Wave (8s)
    print("\n[Style 1/4] The Hip Wiper / Lateral Fan Wave (8s)...")
    print("-> Large lateral hip sweeps across the sky with elevated knee.")
    spec_wiper = {
        "name": "waveHipWiper",
        "fl": TRIPOD_BASE["fl"],
        "fr": TRIPOD_BASE["fr"],
        "bl": TRIPOD_BASE["bl"],
        "br": {
            "mode": "walk",
            "period": 550,
            "ampSpread": 32,
            "ampHeight": 8,
            "phase": 0,
            "spread": 45,
            "height": 40,
            "direction": "forward"
        }
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_wiper)
    time.sleep(8.0)

    # Style 2: The 2-DOF Sky Circle / Lasso Orbit (8s)
    print("\n[Style 2/4] The 2-DOF Sky Circle / Lasso Orbit (8s)...")
    print("-> Coordinated hip + knee rolling in 90-deg phase offset circles.")
    spec_circle = {
        "name": "waveSkyCircle",
        "fl": TRIPOD_BASE["fl"],
        "fr": TRIPOD_BASE["fr"],
        "bl": TRIPOD_BASE["bl"],
        "br": {
            "mode": "walk",
            "period": 800,
            "ampSpread": 26,
            "ampHeight": 24,
            "phase": 0,
            "spread": 40,
            "height": 35,
            "direction": "forward"
        }
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_circle)
    time.sleep(8.0)

    # Style 3: The Rapid High-Five Paw Flutter (7s)
    print("\n[Style 3/4] The Rapid High-Five Flutter (7s)...")
    print("-> Fast, cheerful 280ms paw waving with wide hip angle.")
    spec_flutter = {
        "name": "waveFlutter",
        "fl": TRIPOD_BASE["fl"],
        "fr": TRIPOD_BASE["fr"],
        "bl": TRIPOD_BASE["bl"],
        "br": {
            "mode": "flex",
            "period": 280,
            "amplitude": 30,
            "phase": 0,
            "spread": 50,
            "height": 35
        }
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_flutter)
    time.sleep(7.0)

    # Style 4: The Majestic Slow Reverse Swirl (7s)
    print("\n[Style 4/4] The Majestic Reverse Swirl & Beckon (7s)...")
    print("-> Slow, grand 1400ms sweeping arc with reverse orbital direction.")
    spec_swirl = {
        "name": "waveReverseSwirl",
        "fl": TRIPOD_BASE["fl"],
        "fr": TRIPOD_BASE["fr"],
        "bl": TRIPOD_BASE["bl"],
        "br": {
            "mode": "walk",
            "period": 1400,
            "ampSpread": 34,
            "ampHeight": 28,
            "phase": 0,
            "spread": 45,
            "height": 35,
            "direction": "backward"
        }
    }
    robot.send_command("stop")
    time.sleep(0.15)
    robot.send_spec(spec_swirl)
    time.sleep(7.0)

    # Clean landing & relax
    print("\n[Finish] Lowering leg and easing into neutral rest...")
    robot.send_spec(prep_spec)
    time.sleep(1.0)
    robot.send_command("stop")
    print("-> Wave spectacular complete! FairyKame relaxed.\n")

if __name__ == "__main__":
    wave_hind_right()
