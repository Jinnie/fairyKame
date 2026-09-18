#include "commandexecutor.h"

void CommandExecutor::init(MiniKame* kame) {
  robot = kame;
}

void CommandExecutor::parseCommand(String command) {
  if (!robot) return;
  if (command == "__dynamic__") {
    robot->applySpec(Mind::getDynamicSpec());
  } else if (!robot->executeMove(command)) {
    robot->just_relax();
  }
}
