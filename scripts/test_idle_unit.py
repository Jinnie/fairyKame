#!/usr/bin/env python3
"""
Unit tests for Idle Mode across Transport and MCP Server.
Uses mocked transport to verify idle mode transitions, endpoints, and status telemetry.
"""

import sys
import os
import unittest
from unittest.mock import MagicMock, patch

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)

from bridge.transport import WiFiTransport, SerialTransport
import bridge.mcp_server as mcp


class TestIdleMode(unittest.TestCase):

    def test_wifi_transport_set_idle(self):
        with patch("requests.Session") as mock_session_cls:
            mock_session = MagicMock()
            mock_resp = MagicMock()
            mock_resp.status_code = 200
            mock_session.get.return_value = mock_resp
            mock_session_cls.return_value = mock_session

            trans = WiFiTransport(base_url="http://127.0.0.1")
            self.assertTrue(trans.idle_mode)

            # Test enabling idle
            ok = trans.set_idle_mode(True)
            self.assertTrue(ok)
            self.assertTrue(trans.idle_mode)
            mock_session.get.assert_called_with("http://127.0.0.1/idle", params={"idle": 1}, timeout=3.0)

            # Test status reporting
            status = trans.get_status()
            self.assertTrue(status["idle_mode"])

            # Test disabling idle
            ok = trans.set_idle_mode(False)
            self.assertTrue(ok)
            self.assertFalse(trans.idle_mode)
            mock_session.get.assert_called_with("http://127.0.0.1/idle", params={"idle": 0}, timeout=3.0)

            status = trans.get_status()
            self.assertFalse(status["idle_mode"])

    def test_serial_transport_set_idle(self):
        with patch("serial.Serial") as mock_serial_cls:
            mock_ser = MagicMock()
            mock_ser.is_open = True
            mock_serial_cls.return_value = mock_ser

            trans = SerialTransport(port="COM99")
            self.assertTrue(trans.idle_mode)

            # Test enabling idle
            ok = trans.set_idle_mode(True)
            self.assertTrue(ok)
            self.assertTrue(trans.idle_mode)
            mock_ser.write.assert_called_with(b"\nidle_on\n")

            status = trans.get_status()
            self.assertTrue(status["idle_mode"])

            # Test disabling idle
            ok = trans.set_idle_mode(False)
            self.assertTrue(ok)
            self.assertFalse(trans.idle_mode)
            mock_ser.write.assert_called_with(b"\nidle_off\n")

            status = trans.get_status()
            self.assertFalse(status["idle_mode"])

    def test_mcp_idle_tool(self):
        mock_robot = MagicMock()
        mock_robot.set_idle_mode.return_value = True
        mock_robot.get_status.return_value = {"online": True, "idle_mode": True}
        mock_robot.send_command.return_value = True
        mock_robot.idle_mode = True

        mcp.robot = mock_robot

        # Test tool enable
        res = mcp.fairykame_set_idle_mode(True)
        self.assertIn("ENABLED", res)
        mock_robot.set_idle_mode.assert_called_with(True)

        # Test fairykame_stop with idle_mode = True
        stop_res = mcp.fairykame_stop()
        self.assertIn("idle alive breathing loop", stop_res)

        # Test fairykame_pose with "idle"
        pose_res = mcp.fairykame_pose("idle")
        self.assertIn("idle", pose_res)

        # Test tool disable
        mock_robot.idle_mode = False
        res = mcp.fairykame_set_idle_mode(False)
        self.assertIn("DISABLED", res)
        mock_robot.set_idle_mode.assert_called_with(False)

        stop_res = mcp.fairykame_stop()
        self.assertIn("relaxed", stop_res)


if __name__ == "__main__":
    unittest.main()
