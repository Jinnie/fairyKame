#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "soul/octosnake.h"
#include "minikame.h"
#include "soul/webconnector.h"
#include "soul/serialconnector.h"
#include "mind/commandexecutor.h"
#include "mind/mind.h"

MiniKame robot;
WebConnector webConnector;
SerialConnector serialConnector;
CommandExecutor executor;
String activeCommand;

void setup() {
  Serial.begin(115200);
  delay(3000);

  webConnector.init();
  serialConnector.init();
  robot.init();
  executor.init(&robot);
  Serial.println("A Fairy wakes up!");
}

void loop() {
  // if there is a connection waiting, process it
  webConnector.handleConnection();
  serialConnector.handleConnection();

  // get the active command
  if (activeCommand != Mind::getActiveCommand()) {
    robot.stop_work();
  
    activeCommand = Mind::getActiveCommand();
    // execute the active command, which calls the robot
    executor.parseCommand(activeCommand);
  }

  // give it some life
  // we'll use the pulse system to simulate multithreading
  robot.pulse();
  // this delay limits the shortest possible period; want faster robot - then reduce the delay.
  // bigger delay means less accurate, lazy moves. too big values - moves are uneven and amplitudes get out of sync.
  // no delay - slower servos don't get enough time to complete commands; phase may get out of sync.
  // you can play with this setting, to find what's best for your own servos.
  delay(Mind::getDelay());
  yield(); // yield for sync! remove to suffer
}
