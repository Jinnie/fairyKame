"""
FairyKame Roll Over Attempt
Executes a dynamic momentum-based side-roll maneuver to try to flip onto its back.
"""

import sys
import os
import time

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from bridge.transport import get_transport

def roll_over():
    print("Connecting to FairyKame...")
    robot = get_transport("wifi")
    
    # 1. Neutral starting stance
    print("1. Neutral stance...")
    robot.send_command("stop")
    time.sleep(1.0)
    
    # 2. Deep crouch (compress springs / lower center of mass)
    print("2. Deep crouch...")
    crouch_spec = {
        "name": "deepCrouch",
        "fl": [0, 40],
        "fr": [0, 40],
        "bl": [0, 40],
        "br": [0, 40]
    }
    robot.send_spec(crouch_spec)
    time.sleep(1.0)
    
    # 3. Wind-up lean to the left (build potential energy / swing)
    print("3. Wind-up lean left...")
    windup_spec = {
        "name": "windupLeft",
        "fl": [-30, 60],
        "bl": [-30, 60],
        "fr": [30, -30],
        "br": [30, -30]
    }
    robot.send_spec(windup_spec)
    time.sleep(0.8)
    
    # 4. EXPLOSIVE THRUST TO THE RIGHT!
    # Left legs kick down hard (-85 deg), hips throw right (+45 deg).
    # Right legs tuck completely flat against the belly (+85 deg) so they don't block the roll!
    print("4. EXPLOSIVE THRUST ROLL RIGHT!")
    thrust_spec = {
        "name": "thrustRollRight",
        "fl": [45, -85],
        "bl": [45, -85],
        "fr": [-30, 85],
        "br": [-30, 85]
    }
    robot.send_spec(thrust_spec)
    time.sleep(0.6)
    
    # 5. Follow-through: Tuck left legs as well to complete the roll
    print("5. Follow-through roll...")
    follow_spec = {
        "name": "followThrough",
        "fl": [30, 60],
        "bl": [30, 60],
        "fr": [-30, 85],
        "br": [-30, 85]
    }
    robot.send_spec(follow_spec)
    time.sleep(0.6)
    
    # 6. Belly Up (Flipped Turtle pose: all 4 legs pointing into the sky!)
    print("6. Belly Up / Turtle on back pose!")
    belly_up_spec = {
        "name": "bellyUp",
        "fl": [40, 75],
        "fr": [-40, 75],
        "bl": [-40, 75],
        "br": [40, 75]
    }
    robot.send_spec(belly_up_spec)
    time.sleep(2.0)
    
    # 7. Wiggle feet in the air!
    print("7. Wiggling feet in the air...")
    wiggle_spec = {
        "name": "turtleWiggle",
        "fl": {"mode": "flex", "period": 350, "amplitude": 25, "phase": 0, "spread": 40, "height": 70},
        "fr": {"mode": "flex", "period": 350, "amplitude": 25, "phase": 90, "spread": -40, "height": 70},
        "bl": {"mode": "flex", "period": 350, "amplitude": 25, "phase": 180, "spread": -40, "height": 70},
        "br": {"mode": "flex", "period": 350, "amplitude": 25, "phase": 270, "spread": 40, "height": 70}
    }
    robot.send_spec(wiggle_spec)
    time.sleep(4.0)
    
    print("Roll-over sequence complete!")

if __name__ == "__main__":
    roll_over()
