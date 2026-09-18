#include <Arduino.h>
#include "minikame.h"
#ifndef DISABLE_WIFI
#include "soul/webconnector.h"
#endif
#ifndef DISABLE_SERIAL
#include "soul/serialconnector.h"
#endif
#include "mind/commandexecutor.h"
#include "mind/mind.h"

MiniKame robot;
#ifndef DISABLE_WIFI
WebConnector webConnector;
#endif
#ifndef DISABLE_SERIAL
SerialConnector serialConnector;
#endif
CommandExecutor executor;
String activeCommand;

void setup() {
  Serial.begin(115200);
  delay(3000);

#ifndef DISABLE_WIFI
  webConnector.init();
#endif
#ifndef DISABLE_SERIAL
  serialConnector.init();
#endif
  robot.init();
  executor.init(&robot);
  Serial.println("A Fairy wakes up!");
}

void loop() {
  // if there is a connection waiting, process it
#ifndef DISABLE_WIFI
  webConnector.handleConnection();
#endif
#ifndef DISABLE_SERIAL
  serialConnector.handleConnection();
#endif

  // get the active command
  if (activeCommand != Mind::getActiveCommand() || Mind::isDynamicSpecDirty()) {
    robot.stop_work();
  
    Mind::clearDynamicSpecDirty();
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
