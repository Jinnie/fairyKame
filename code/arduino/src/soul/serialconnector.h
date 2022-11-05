#ifndef serialconnector_h
#define serialconnector_h

#include <ESP8266WiFi.h>
#include "mind/mind.h"

class SerialConnector {
  public:
    void init();
    void handleConnection();
};

#endif
