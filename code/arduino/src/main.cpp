#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "soul/octosnake.h"
#include "minikame.h"
#include "soul/webconnector.h"
#include "mind/commandexecutor.h"
#include "mind/mind.h"

MiniKame robot;
WebConnector connector;
CommandExecutor executor;
String activeCommand;

void setup() {
  Serial.begin(115200);
  delay(3000);

  connector.init();
  robot.init();
  executor.init(&robot);
  Serial.println("Robot is starting.");
  Mind::start_work();
}

void loop() {
  // On previous iteration it was requested to stop all activities.
  // All done - this iteration we go on as normal.
  if (Mind::in_rest()) {
    Mind::start_work();
  }
  // if there is a connection waiting, process it
  connector.handleConnection();
  // get the active command
  if (activeCommand != connector.getActiveCommand()) {
    //Stop all activities
    Mind::stop_work();
    activeCommand = connector.getActiveCommand();
  }

  // execute the active command, which calls the robot
  executor.parseCommand(activeCommand);

  // give it some life
  // we'll use the pulse system to simulate multithreading
  robot.pulse();
  // this delay limits the shortest possible period; want faster robot - then reduce the delay.
  // bigger delay means less accurate, lazy moves. too big values - moves are uneven and amplitudes get out of sync.
  // no delay - slower servos don't get enough time to complete commands; phase may get out of sync.
  // you can play with this setting, to find what's best for your own servos.
  delay(50);
  yield(); // yield for sync! remove to suffer
}
