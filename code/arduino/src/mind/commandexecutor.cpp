#include "commandexecutor.h"

// TODO not sure where this code belongs and if we need this class at all

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
  } else if (command == "dance") {
    robot->just_dance();
  } else if (command == "moonWalk") {
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
  } else if (command == "pushUps") {
    robot->just_pushUps();
  } else if (command == "sayHi") {
    robot->just_say_hi();
  } else if (command == "pack") {
    robot->just_pack();
  } else if (command == "strafeLeft") {
    robot->just_strafe_left();
  } else if (command == "strafeRight") {
    robot->just_strafe_right();
  } else if (command == "turnInPlaceL") {
    robot->just_turn_in_place(true);
  } else if (command == "turnInPlaceR") {
    robot->just_turn_in_place(false);
  } else if (command == "crawl") {
    robot->just_crawl();
  } else if (command == "tiptoe") {
    robot->just_tiptoe();
  } else if (command == "recover") {
    robot->just_recover();
  } else if (command == "sit") {
    robot->just_sit();
  } else if (command == "playDead") {
    robot->just_play_dead();
  } else if (command == "shiver") {
    robot->just_shiver();
  } else if (command == "scratchEar") {
    robot->just_scratch_ear();
  } else if (command == "pouncePrep") {
    robot->just_pounce_prep();
  } else if (command == "waveGoodbye") {
    robot->just_say_hi();
  } else if (command == "tapFoot") {
    robot->just_tap_foot();
  } else {
    robot->just_relax();
  }
}
