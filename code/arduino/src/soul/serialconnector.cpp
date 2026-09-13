#include "serialconnector.h"

void SerialConnector::init()
{
  Serial.println("Serial fishes swimming");
  Serial.println("  Hold WASD/diagonals/,/. to move (auto-stops on release), Space to stop, Tab for Magic, Enter to type a command.");
  Serial.setTimeout(5000);
}

void SerialConnector::handleConnection()
{
  unsigned long now = millis();

  if (this->isMomentary) {
    if (Mind::getActiveCommand() == "stop") {
      this->isMomentary = false;
    } else if (now - this->lastMovementTime > this->momentaryTimeout) {
      this->isMomentary = false;
      Mind::setActiveCommand("stop");
    }
  }

  if (Serial.available() > 0) {
    String cmd = "stop";
    bool keyRecognized = false;
    bool momentaryKey = false;

    if (!readCmd) {
      int cmdCode = Serial.read();

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
          readCmd = true;
          break;
        default:
          break;
      }
    } else {
      cmd = Serial.readStringUntil('\n');
      cmd.trim();
      readCmd = false;
      keyRecognized = true;
      momentaryKey = false;
    }

    if (!readCmd && keyRecognized) {
      if (momentaryKey) {
        this->momentaryTimeout = this->isMomentary ? 350 : 500;
        this->isMomentary = true;
        this->lastMovementTime = millis();
      } else {
        this->isMomentary = false;
      }
      Mind::setActiveCommand(cmd);
    }
  }
}
