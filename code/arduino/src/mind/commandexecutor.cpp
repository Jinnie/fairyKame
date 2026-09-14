#include "commandexecutor.h"

void CommandExecutor::init(MiniKame* kame) {
  robot = kame;
}

void CommandExecutor::parseCommand(String command) {
  if (!robot || !robot->executeMove(command)) {
    if (robot) {
      robot->just_relax();
    }
  }
}
