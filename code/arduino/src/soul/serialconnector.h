#ifndef serialconnector_h
#define serialconnector_h

#ifndef DISABLE_SERIAL

#include <Arduino.h>
#include "mind/mind.h"
#include "connector.h"

class SerialConnector : public Connector {
  public:
    void init() override;
    void handleConnection() override;
  private:
    boolean readCmd = false;
    unsigned long lastMovementTime = 0;
    unsigned long momentaryTimeout = 350;
    bool isMomentary = false;
};

#endif // DISABLE_SERIAL

#endif // serialconnector_h

