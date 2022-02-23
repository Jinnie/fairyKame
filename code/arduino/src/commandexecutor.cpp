#include "commandexecutor.h"

void CommandExecutor::init(MiniKame* kame) {
  robot = kame;
}

void CommandExecutor::parseCommand(String command) {

  if (command == "run") {
    robot->just_walk();
  } else if (command == "turnL") {
    robot->just_left();
  } else if (command == "turnR") {
    robot->just_right();
  } else if (command == "back") {
    robot->just_back();
  } else if (command == "stop") {
    robot->just_relax();
    delay(100);
  // } else if (command == "pushUp") {
  //   robot->pushUp(2,1400);
  // } else if (command == "upDown") {
  //   robot->upDown(4,250);
  // } else if (command == "jump") {
  //   robot->jump();
  // } else if (command == "hello") {
  //   robot->hello();
  // } else if (command == "frontBack") {
  //   robot->frontBack(4,200);
  } else if (command == "dance") {
    // robot->dance(2,1000);
    robot->just_dance();
  } else if (command == "moonWalk") {
    // robot->moonwalkL(4,2000);
    robot->just_moonwalk();
  } else if (command == "magic") {
    robot->magic();
  } else if (command == "jiggle") {
    robot->just_jiggle();
  } else if (command == "stretch") {
    robot->just_stretch();
  } else if (command == "upLeft") {
    robot->just_upLeft();
  } else if (command == "upRight") {
    robot->just_upRight();
  } else if (command == "backLeft") {
    robot->just_backLeft();
  } else if (command == "backRight") {
    robot->just_backRight();
  } else if (command == "confused") {
    robot->just_confused();
  } else {
    robot->just_relax();
    delay(100);
  }
}
