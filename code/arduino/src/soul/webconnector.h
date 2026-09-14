#ifndef webconnector_h
#define webconnector_h

#ifndef DISABLE_WIFI

#if __has_include("secrets.h")
#include "secrets.h"
#endif

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef DISABLE_OTA
#include <ArduinoOTA.h>
#endif

#include "mind/mind.h"
#include "connector.h"


class WebConnector : public Connector {
  public:
    static void handleRoot();
    static void handleCommand();
    static void handleTrim();
    static void handleTilt();
    static void handleSpeed();
    static void handleDelay();
    // Initialize the server
    void init() override;
    void handleConnection() override;

  private:
    bool otaActive = false;
};

#endif // DISABLE_WIFI

#endif // webconnector_h

