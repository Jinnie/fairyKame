#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "octosnake.h"
#include "minikame.h"
#include "sensoreyes.h"
#include "webconnector.h"
#include "commandexecutor.h"
#include "mind/mind.h"

MiniKame robot;
SensorEyes eyes;
WebConnector connector;
CommandExecutor executor;
String activeCommand;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // assign SD_DATA2 and SD_DATA2 GPIO function
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA2_U, FUNC_GPIO9);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA3_U, FUNC_GPIO10);

  connector.init();
  robot.init();
  eyes.init();
  executor.init(&robot);
  Serial.println("Robot is starting.");
  Mind::start_work();
}

void loop() {
  // Previous iteration it requested stop all activities.
  // All done - this iteration go on as normal.
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

  // todo: this should be handled in a robot head or something
  if (executor.isAutonomous()) {
      // the good stuff, not very smart yet. Tryouts.
      eyes.measureDistance();
      if (eyes.getDistance() == 0 ||  eyes.getDistance() > 20) {
        // just run, and for the moment, run into a wall if we get no values
        executor.parseCommand("run");
      } else {
        // something is in the way, try to go right
        executor.parseCommand("turnR");
      }
  }
  // execute the active command, which calls the robot
  executor.parseCommand(activeCommand);

  // give it some life
  // we'll use the pulse system to simulate multithreading
  robot.pulse();
  delay(50);  // test longer values
  yield(); // yield for sync!
}
