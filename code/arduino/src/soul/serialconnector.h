#ifndef serialconnector_h
#define serialconnector_h

#include <Arduino.h>
#include "mind/mind.h"

class SerialConnector {
  public:
    void init();
    void handleConnection();
  private:
    boolean readCmd = false;
    unsigned long lastMovementTime = 0;
    unsigned long momentaryTimeout = 350;
    bool isMomentary = false;
};

#endif
