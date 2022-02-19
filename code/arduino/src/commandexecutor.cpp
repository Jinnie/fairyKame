#include "commandexecutor.h"

void CommandExecutor::init(MiniKame* kame) {
  robot = kame;
  autonomous = false;
}

void CommandExecutor::parseCommand(String command) {

  if (command == "run") {
    // robot->run(1,550);
    robot->just_walk();
  } else if (command == "turnL") {
    // robot->turnL(1,550);
    robot->just_left();
  } else if (command == "turnR") {
    // robot->turnR(1,550);
    robot->just_right();
  } else if (command == "back") {
    robot->just_back();
  } else if (command == "stop") {
    autonomous = false;
    robot->home();
    delay(100);
  } else if (command == "pushUp") {
    robot->pushUp(2,1400);
  } else if (command == "upDown") {
    robot->upDown(4,250);
  } else if (command == "jump") {
    robot->jump();
  } else if (command == "hello") {
    robot->hello();
  } else if (command == "frontBack") {
    robot->frontBack(4,200);
  } else if (command == "dance") {
    robot->dance(2,1000);
  } else if (command == "moonWalk") {
    robot->moonwalkL(4,2000);
  } else if (command == "magic") {
    robot->magic();
  } else if (command == "auto") {
    autonomous = true;
  } else {
    robot->home();
    delay(100);
  }
}

boolean CommandExecutor::isAutonomous() {
    return autonomous;
}
