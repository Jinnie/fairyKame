#include "serialconnector.h"

void SerialConnector::init()
{
  Serial.println("Serial fishes swimming");
  Serial.println("  Use WASD keys to move, Space to stop, Tab for Magic key, or Enter to type a command.");
  Serial.setTimeout(5000);
}

void SerialConnector::handleConnection()
{
  if (Serial.available() > 0) {
    
    String cmd = "stop";

    if (!readCmd) {
      int cmdCode = Serial.read();

      Serial.print("->");
      Serial.println(cmdCode);

      switch (cmdCode) {
        case 32: cmd = "stop"; // Space
        break;
        case 'w':
        case 'W': cmd = "run";
        break;
        case 's':
        case 'S':
        case 'x':
        case 'X': cmd = "back";
        break;
        case 'a':
        case 'A': cmd = "turnL";
        break;
        case 'd':
        case 'D': cmd = "turnR";
        break;
        case 'q':
        case 'Q': cmd = "upLeft";
        break;
        case 'e':
        case 'E': cmd = "upRight";
        break;
        case 'z':
        case 'Z': cmd = "backLeft";
        break;
        case 'c':
        case 'C': cmd = "backRight";
        break;
        case 44: cmd = "strafeLeft"; // ,
        break;
        case 46: cmd = "strafeRight"; // .
        break;
        case 9: cmd = "magic"; // Tab
        break;
        case 10: // LF
        case 13: // CR
        Serial.println("Type command");
        readCmd = true;
        break;
      }
    } else {
      cmd = Serial.readStringUntil('\n');
      cmd.trim();
      readCmd = false;
    }
    if (!readCmd) {
      Mind::setActiveCommand(cmd);
    }
  }
}
