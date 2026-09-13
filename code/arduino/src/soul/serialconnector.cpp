#include "serialconnector.h"

void SerialConnector::init()
{
  Serial.println("Serial fishes swimming");
  Serial.println("  Hold WASD/diagonals/,/. to move (auto-stops on release), Space to stop, Tab for Magic, Enter to type a command.");
  Serial.setTimeout(5000);
}

void SerialConnector::handleConnection()
{
  while (Serial.available() > 0) {
    if (this->readCmd) {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();
      this->readCmd = false;
      this->isMomentary = false;
      if (cmd.length() > 0) {
        Mind::setActiveCommand(cmd);
      }
      break;
    }

    int cmdCode = Serial.read();
    String cmd = "";
    bool keyRecognized = false;
    bool momentaryKey = false;

    switch (cmdCode) {
      case 32: // Space
        cmd = "stop";
        keyRecognized = true;
        momentaryKey = false;
        break;
      case 'w':
      case 'W':
        cmd = "run";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 's':
      case 'S':
      case 'x':
      case 'X':
        cmd = "back";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'a':
      case 'A':
        cmd = "turnL";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'd':
      case 'D':
        cmd = "turnR";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'q':
      case 'Q':
        cmd = "upLeft";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'e':
      case 'E':
        cmd = "upRight";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'z':
      case 'Z':
        cmd = "backLeft";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 'c':
      case 'C':
        cmd = "backRight";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 44: // ,
        cmd = "strafeLeft";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 46: // .
        cmd = "strafeRight";
        keyRecognized = true;
        momentaryKey = true;
        break;
      case 9: // Tab
        cmd = "magic";
        keyRecognized = true;
        momentaryKey = false;
        break;
      case 10: // LF
      case 13: // CR
        Serial.println("Type command");
        this->readCmd = true;
        break;
      default:
        break;
    }

    if (!this->readCmd && keyRecognized) {
      if (momentaryKey) {
        this->momentaryTimeout = this->isMomentary ? 200 : 450;
        this->isMomentary = true;
        this->lastMovementTime = millis();
      } else {
        this->isMomentary = false;
      }
      Mind::setActiveCommand(cmd);
    }
  }

  // Dead-man's switch: auto-stop when momentary movement keys stop repeating
  unsigned long now = millis();
  if (this->isMomentary) {
    if (Mind::getActiveCommand() == "stop") {
      this->isMomentary = false;
    } else if (now - this->lastMovementTime > this->momentaryTimeout) {
      this->isMomentary = false;
      Mind::setActiveCommand("stop");
    }
  }
}
