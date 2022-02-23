#ifndef commandexecutor_h
#define commandexecutor_h

#include <Arduino.h>
#include "minikame.h"
class CommandExecutor {
  public:
    void init(MiniKame* kame);
    void parseCommand(String command);
    // boolean isAutonomous();
  private:
    MiniKame * robot;
    // bool autonomous;
};
#endif
