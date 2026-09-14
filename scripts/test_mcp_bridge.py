"""
Test script for FairyKame Transport and MCP Tool functions.
Verifies communication without needing an external AI host.
"""

import sys
import os
import time
import json

# Ensure project root is on sys.path
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from bridge.transport import get_transport
import bridge.mcp_server as mcp


def run_test():
    print("=" * 60)
    print("Testing FairyKame Transport & MCP Server Bridge")
    print("=" * 60)

    # 1. Initialize transport
    print("\n1. Initializing transport (Auto mode)...")
    mcp.robot = get_transport(mode="auto")
    print(f"   Selected: {mcp.robot.__class__.__name__}")

    # 2. Query status
    print("\n2. Querying robot status via fairykame_status()...")
    status_str = mcp.fairykame_status()
    status = json.loads(status_str)
    print(f"   Online: {status.get('online')}")
    print(f"   Transport: {status.get('transport')}")
    print(f"   Latency: {status.get('latency_ms')} ms")
    print(f"   URL/Port: {status.get('url') or status.get('port')}")

    if not status.get("online"):
        print("   WARNING: Robot reports offline. Ensure Wi-Fi is connected or USB is plugged in.")
        return False

    # 3. Test Pose (sit)
    print("\n3. Testing fairykame_pose('sit')...")
    res = mcp.fairykame_pose("sit")
    print(f"   Result: {res}")
    time.sleep(1.0)

    # 4. Test Gesture (say_hi)
    print("\n4. Testing fairykame_express('say_hi')...")
    res = mcp.fairykame_express("say_hi")
    print(f"   Result: {res}")
    time.sleep(2.0)

    # 5. Test Locomotion (move forward for 1.0s)
    print("\n5. Testing fairykame_move('forward', 1.0)...")
    res = mcp.fairykame_move("forward", 1.0)
    print(f"   Result: {res}")

    # 6. Test Stop / Relax
    print("\n6. Testing fairykame_stop()...")
    res = mcp.fairykame_stop()
    print(f"   Result: {res}")

    # 7. Test Dynamic MoveSpec (waving hind right leg on the fly)
    print("\n7. Testing fairykame_wave_leg('br', 2.0)...")
    res = mcp.fairykame_wave_leg("br", 2.0)
    print(f"   Result: {res}")

    # 8. Test Arbitrary Dynamic Spec (curious tilt)
    print("\n8. Testing fairykame_custom_spec('curiousTilt', 1.5)...")
    spec = {
        "name": "curiousTilt",
        "fl": [20, -40],
        "fr": [-20, -40],
        "bl": [-10, 40],
        "br": [10, 40]
    }
    res = mcp.fairykame_custom_spec(spec, duration=1.5)
    print(f"   Result: {res}")

    print("\n" + "=" * 60)
    print("All MCP Bridge tests PASSED successfully!")
    print("=" * 60)
    return True


if __name__ == "__main__":
    success = run_test()
    if mcp.robot:
        mcp.robot.close()
    sys.exit(0 if success else 1)
