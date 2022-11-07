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
        case 119: cmd = "run"; // W
        break;
        case 120: cmd = "back"; // X
        break;
        case 97: cmd = "turnL"; // A
        break;
        case 100: cmd = "turnR"; // D
        break;
        case 113: cmd = "upLeft"; // Q
        break;
        case 101: cmd = "upRight"; // E
        break;
        case 122: cmd = "backLeft"; // Z
        break;
        case 99: cmd = "backRight"; // C
        break;
        case 44: cmd = "strafeLeft"; // ,
        break;
        case 46: cmd = "strafeRight"; // .
        break;
        case 9: cmd = "magic"; // Tab
        break;
        case 10:
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
