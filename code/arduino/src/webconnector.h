#ifndef webconnector_h
#define webconnector_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



class WebConnector {
  public:
    static void handleRoot();
    static void handleCommand();
    // Initialize the server
    void init();
    void handleConnection();
    String getActiveCommand();
  private:
    static String activeCommand;
};

#endif
