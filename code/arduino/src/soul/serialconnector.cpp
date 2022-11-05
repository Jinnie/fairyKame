#include "serialconnector.h"

void SerialConnector::init()
{

  Serial.println("Serial connector started");
  Serial.println("You can use WASD keys to move, Space to stop and Tab for Magic key.");
}

void SerialConnector::handleConnection()
{
  if (Serial.available() > 0) {
    int cmdCode = Serial.read();

    Serial.print("Received: ");
    Serial.println(cmdCode);

    String cmd = "stop";

    switch (cmdCode) {
      case 32: cmd = "stop"; // Space
      break;
      case 119: cmd = "run"; // W
      break;
      case 115: cmd = "back"; // S
      break;
      case 97: cmd = "turnL"; // A
      break;
      case 100: cmd = "turnR"; // D
      break;
      case 9: cmd = "magic"; // Tab
      break;
    }
    
    Mind::setActiveCommand(cmd);
  }
}
