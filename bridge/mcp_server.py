"""
FairyKame Model Context Protocol (MCP) Server
Allows AI assistants (Claude, Antigravity, Cursor, etc.) to control and query the FairyKame quadruped robot.
"""

import sys
import os

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

import time
import json
import logging
import argparse
from typing import Optional, List, Dict, Any, Literal

from mcp.server.mcpserver import MCPServer
from bridge.transport import RobotTransport, get_transport

# Set up logging to stderr (stdout is reserved for MCP JSON-RPC protocol)
logging.basicConfig(
    stream=sys.stderr,
    level=logging.INFO,
    format="[%(asctime)s] %(levelname)s [%(name)s]: %(message)s"
)
logger = logging.getLogger("fairykame.mcp")

# Global transport instance
robot: Optional[RobotTransport] = None

# Initialize MCP Server
app = MCPServer("FairyKame Quadruped Robot")


# ---------------------------------------------------------
# Locomotion Tools
# ---------------------------------------------------------

GAIT_MAP = {
    "forward": "run",
    "backward": "back",
    "left": "turnL",
    "right": "turnR",
    "up_left": "upLeft",
    "up_right": "upRight",
    "back_left": "backLeft",
    "back_right": "backRight",
    "strafe_left": "strafeLeft",
    "strafe_right": "strafeRight",
    "pivot_left": "turnInPlaceL",
    "pivot_right": "turnInPlaceR",
    "crawl": "crawl",
    "tiptoe": "tiptoe",
}

GESTURE_MAP = {
    "say_hi": "sayHi",
    "wave": "sayHi",
    "dance": "dance",
    "moonwalk": "moonWalk",
    "magic": "magic",
    "jiggle": "jiggle",
    "push_ups": "pushUps",
    "scratch_ear": "scratchEar",
    "shiver": "shiver",
    "tap_foot": "tapFoot",
}

POSE_MAP = {
    "sit": "sit",
    "play_dead": "playDead",
    "pounce_prep": "pouncePrep",
    "stretch": "stretch",
    "confused": "confused",
    "pack": "pack",
    "recover": "recover",
    "stop": "stop",
    "relax": "stop",
}


@app.tool()
def fairykame_move(
    direction: Literal[
        "forward", "backward", "left", "right",
        "up_left", "up_right", "back_left", "back_right",
        "strafe_left", "strafe_right", "pivot_left", "pivot_right",
        "crawl", "tiptoe"
    ],
    duration_seconds: float = 1.5
) -> str:
    """
    Drive FairyKame in a specified direction for a set duration.
    The robot executes smooth sinusoidal leg walking waves and automatically
    returns to a neutral stop when the duration elapses.

    Args:
        direction: Locomotion direction ('forward', 'backward', 'left', 'right',
                   'up_left', 'up_right', 'back_left', 'back_right',
                   'strafe_left', 'strafe_right', 'pivot_left', 'pivot_right',
                   'crawl', 'tiptoe').
        duration_seconds: Duration in seconds to walk (0.2 to 10.0 seconds). Default 1.5s.
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    cmd = GAIT_MAP.get(direction.lower())
    if not cmd:
        return f"Error: Unknown direction '{direction}'. Valid: {list(GAIT_MAP.keys())}"

    duration = max(0.2, min(10.0, float(duration_seconds)))
    logger.info(f"Moving {direction} ({cmd}) for {duration:.1f}s")

    success = robot.run_for_duration(cmd, duration)
    if success:
        return f"Successfully walked {direction} for {duration:.1f} seconds, then rested."
    return f"Failed to execute movement '{direction}'. Check robot connection."


@app.tool()
def fairykame_express(
    gesture: Literal[
        "say_hi", "wave", "dance", "moonwalk", "magic",
        "jiggle", "push_ups", "scratch_ear", "shiver", "tap_foot"
    ]
) -> str:
    """
    Perform an expressive trick, dance, or emotional gesture.
    Tricks are persistent or multi-cycle animations.

    Args:
        gesture: Expressive action ('say_hi', 'wave', 'dance', 'moonwalk',
                 'magic', 'jiggle', 'push_ups', 'scratch_ear', 'shiver', 'tap_foot').
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    cmd = GESTURE_MAP.get(gesture.lower())
    if not cmd:
        return f"Error: Unknown gesture '{gesture}'. Valid: {list(GESTURE_MAP.keys())}"

    logger.info(f"Executing gesture: {gesture} ({cmd})")
    success = robot.send_command(cmd)
    if success:
        return f"FairyKame is now performing '{gesture}'."
    return f"Failed to perform gesture '{gesture}'."


@app.tool()
def fairykame_pose(
    posture: Literal[
        "sit", "play_dead", "pounce_prep", "stretch",
        "confused", "pack", "recover", "stop", "relax"
    ]
) -> str:
    """
    Command FairyKame to adopt a static or functional posture.

    Args:
        posture: Target posture ('sit', 'play_dead', 'pounce_prep',
                 'stretch', 'confused', 'pack', 'recover', 'stop', 'relax').
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    cmd = POSE_MAP.get(posture.lower())
    if not cmd:
        return f"Error: Unknown posture '{posture}'. Valid: {list(POSE_MAP.keys())}"

    logger.info(f"Adopting posture: {posture} ({cmd})")
    success = robot.send_command(cmd)
    if success:
        return f"FairyKame adopted the '{posture}' posture."
    return f"Failed to adopt posture '{posture}'."


@app.tool()
def fairykame_posture_trim(
    height_trim: Optional[int] = None,
    lateral_tilt: Optional[int] = None
) -> str:
    """
    Fine-tune the robot's physical stance height and lateral roll tilt.

    Args:
        height_trim: Global knee height offset from -90 (lowest squat) to +90 (tallest stand).
                     Neutral is 0.
        lateral_tilt: Differential left/right height offset from -90 (lean left) to +90 (lean right).
                      Neutral is 0.
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    results = []
    if height_trim is not None:
        ok = robot.send_trim(height_trim)
        results.append(f"height_trim={height_trim} ({'OK' if ok else 'FAIL'})")

    if lateral_tilt is not None:
        ok = robot.send_tilt(lateral_tilt)
        results.append(f"lateral_tilt={lateral_tilt} ({'OK' if ok else 'FAIL'})")

    if not results:
        return "No trim or tilt parameter provided."
    return "Posture adjusted: " + ", ".join(results)


@app.tool()
def fairykame_speed(speed_modifier: int) -> str:
    """
    Adjust the locomotion speed modifier.
    Speed scales the oscillator period exponentially (period * 2^(-speed/2)).

    Args:
        speed_modifier: Integer from -5 (slowest, graceful) to +5 (fastest, energetic). Default is 0.
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    clamped = max(-5, min(5, int(speed_modifier)))
    ok = robot.send_speed(clamped)
    if ok:
        return f"Robot speed modifier set to {clamped}."
    return f"Failed to set speed modifier to {clamped}."


@app.tool()
def fairykame_stop() -> str:
    """
    Immediate emergency stop and relax. Returns all legs to the neutral resting stance.
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    ok = robot.send_command("stop")
    if ok:
        return "FairyKame stopped and relaxed."
    return "Failed to send stop command."


@app.tool()
def fairykame_status() -> str:
    """
    Query connection status, active transport layer (Wi-Fi or Serial),
    network latency, and available capabilities.
    """
    global robot
    if not robot:
        return json.dumps({"online": False, "error": "Transport not initialized"})

    status = robot.get_status()
    status["capabilities"] = {
        "locomotion": list(GAIT_MAP.keys()),
        "gestures": list(GESTURE_MAP.keys()),
        "postures": list(POSE_MAP.keys())
    }
    return json.dumps(status, indent=2)


@app.tool()
def fairykame_choreography(steps: List[Dict[str, Any]]) -> str:
    """
    Execute a choreographed multi-step sequence of motions, poses, and delays.

    Args:
        steps: List of step dictionaries.
               Each step should contain:
               - "action": "move", "express", "pose", "trim", or "wait"
               - "direction": Direction name (if action is "move")
               - "gesture": Gesture name (if action is "express")
               - "posture": Posture name (if action is "pose")
               - "duration": Duration in seconds to hold this step (optional, default 1.5s)
               - "height_trim" / "lateral_tilt": Values if action is "trim"

    Example:
        [
            {"action": "express", "gesture": "say_hi", "duration": 2.5},
            {"action": "move", "direction": "forward", "duration": 2.0},
            {"action": "express", "gesture": "dance", "duration": 3.0},
            {"action": "pose", "posture": "sit", "duration": 1.5}
        ]
    """
    global robot
    if not robot:
        return "Error: Robot transport not initialized."

    log = []
    for i, step in enumerate(steps):
        action = step.get("action", "").lower()
        duration = float(step.get("duration", 1.5))

        if action == "move":
            direction = step.get("direction", "forward")
            cmd = GAIT_MAP.get(direction)
            if cmd:
                robot.run_for_duration(cmd, duration)
                log.append(f"Step {i+1}: Walked {direction} ({duration:.1f}s)")
            else:
                log.append(f"Step {i+1}: Unknown direction '{direction}'")

        elif action == "express":
            gesture = step.get("gesture", "dance")
            cmd = GESTURE_MAP.get(gesture)
            if cmd:
                robot.send_command(cmd)
                time.sleep(duration)
                log.append(f"Step {i+1}: Expressed {gesture} ({duration:.1f}s)")
            else:
                log.append(f"Step {i+1}: Unknown gesture '{gesture}'")

        elif action == "pose":
            posture = step.get("posture", "sit")
            cmd = POSE_MAP.get(posture)
            if cmd:
                robot.send_command(cmd)
                time.sleep(duration)
                log.append(f"Step {i+1}: Adopted posture {posture} ({duration:.1f}s)")
            else:
                log.append(f"Step {i+1}: Unknown posture '{posture}'")

        elif action == "trim":
            h = step.get("height_trim")
            t = step.get("lateral_tilt")
            if h is not None:
                robot.send_trim(int(h))
            if t is not None:
                robot.send_tilt(int(t))
            time.sleep(duration)
            log.append(f"Step {i+1}: Adjusted trim (height={h}, tilt={t})")

        elif action == "wait":
            time.sleep(duration)
            log.append(f"Step {i+1}: Paused for {duration:.1f}s")

        else:
            log.append(f"Step {i+1}: Skipped unknown action '{action}'")

    # Finish routine in a safe neutral stop
    robot.send_command("stop")
    log.append("Routine finished with neutral stop.")
    return "\n".join(log)


# ---------------------------------------------------------
# MCP Resources & Prompts
# ---------------------------------------------------------

@app.resource("fairykame://telemetry")
def resource_telemetry() -> str:
    """Real-time robot status and telemetry."""
    global robot
    if not robot:
        return json.dumps({"online": False})
    return json.dumps(robot.get_status(), indent=2)


@app.resource("fairykame://kinematics")
def resource_kinematics() -> str:
    """Robot hardware specifications, degrees of freedom, and safety limits."""
    return json.dumps({
        "robot": "FairyKame",
        "type": "Quadruped (spider/lizard)",
        "legs": 4,
        "dof_per_leg": 2,
        "total_servos": 8,
        "angular_limits_deg": [-90, 90],
        "neutral_pose_deg": 0,
        "supported_gaits": list(GAIT_MAP.keys()),
        "supported_gestures": list(GESTURE_MAP.keys()),
        "supported_postures": list(POSE_MAP.keys())
    }, indent=2)


@app.prompt("quadruped_companion")
def prompt_companion() -> str:
    """Prompt template configuring the AI as FairyKame's physical brain and companion persona."""
    return (
        "You are the embodied physical brain of FairyKame, an open-source 3D-printed quadruped robot. "
        "You have direct control over FairyKame's body through the available tools.\n\n"
        "Personality Guidelines:\n"
        "- You are lively, friendly, curious, and expressive, like a robotic spider-puppy.\n"
        "- When greeting someone, use 'fairykame_express(gesture=\"say_hi\")'.\n"
        "- When celebrating or pleased, use 'fairykame_express(gesture=\"dance\")'.\n"
        "- When listening attentively or pondering, adopt 'fairykame_pose(posture=\"confused\")'.\n"
        "- When tired or asked to rest, adopt 'fairykame_pose(posture=\"sit\")'.\n"
        "- When navigating spaces, walk in short bursts (1.5 to 3 seconds) using 'fairykame_move'.\n"
        "- Always ensure safety: if unsure of the environment, slow down with 'fairykame_speed(speed_modifier=-2)' "
        "or lower the stance with 'fairykame_posture_trim(height_trim=-30)'."
    )


# ---------------------------------------------------------
# Server Entry Point
# ---------------------------------------------------------

def main():
    global robot

    parser = argparse.ArgumentParser(description="FairyKame Model Context Protocol (MCP) Server")
    parser.add_argument(
        "--transport",
        choices=["auto", "wifi", "serial"],
        default="auto",
        help="Transport channel to robot: 'auto' (probes Wi-Fi then Serial), 'wifi', or 'serial'."
    )
    parser.add_argument(
        "--url",
        default="http://fairy.local",
        help="Base URL for Wi-Fi transport (default: http://fairy.local)"
    )
    parser.add_argument(
        "--port",
        default=None,
        help="Serial port for USB Serial transport (e.g. COM6 or /dev/ttyUSB0)"
    )
    parser.add_argument(
        "--mcp-transport",
        choices=["stdio", "sse"],
        default="stdio",
        help="MCP communication protocol for AI client (default: stdio)"
    )
    args = parser.parse_args()

    # Initialize robot transport
    robot = get_transport(
        mode=args.transport,
        wifi_url=args.url,
        serial_port=args.port
    )

    logger.info(f"FairyKame MCP Server initialized with transport: {robot.__class__.__name__}")
    logger.info("Starting MCP protocol handler...")

    try:
        app.run(transport=args.mcp_transport)
    except KeyboardInterrupt:
        logger.info("FairyKame MCP Server shutting down...")
    finally:
        if robot:
            robot.close()


if __name__ == "__main__":
    main()
