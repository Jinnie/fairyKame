#include "webconnector.h"

#ifndef DISABLE_WIFI

const char *ssid = "MINIKAME";
// const char* password = "asdf";

ESP8266WebServer server(80);

const char *page_html = R"CPPHTML(
<!doctype html>
<html>

<head>
    <meta charset="utf-8">
    <title>Mini Kame</title>
    <style>
        .block {
            width: 100%;
        }

        .btn {
            width: 33%;
            height: 120px;
            outline: 1px solid;
            display: inline-block;
            font-size: 24px;
            color: white;
            text-align: center;
            line-height: 500%;
            margin-right: -3px;
        }

        .cB {
            background-color: blue;
        }

        .cBStop {
            background-color: red;
        }

        .cBDir {
            font-size: 40px;
            line-height: 280%;
            background-color: orange;
        }
        .cBDir.dg {
            background-color: blue;
        }
        .cBMgc {
            background-color: green;
            width: 99%;
        }

        .sldLbl {
            color: white;
            font-size: 25px;
            margin-top: 25px;
        }

        .slider {
          -webkit-appearance: none;
          width: 99%;
          height: 50px;
          background: #e3e3e3;
          outline: none;
          -webkit-transition: .2s;
          transition: opacity .2s;
          margin-top: 8px;
          border-top: 4px solid #999999;
          border-bottom: 4px solid #999999;
        }

        .slider::-webkit-slider-thumb {
          -webkit-appearance: none;
          appearance: none;
          width: 50px;
          height: 50px;
          background: #DD7700;
          border-radius: 12px;
          cursor: pointer;
        }

        .slider::-moz-range-thumb {
          width: 50px;
          height: 50px;
          background: #DD7700;
          border-radius: 12px;
          cursor: pointer;
        }

        body {
          background-color: black;
        }
    </style>
    <script type="text/javascript">
      function fireCommand(value) {
        document.getElementById(value).style.background = "black";
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (xhttp.readyState == 4) {
            document.getElementById(value).style.background = '';
          }
        };
        xhttp.open("GET", "cmd?command="+value, true);
        xhttp.send();
      }

      function trim(value) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "trim?trim="+value, true);
        xhttp.send();
        document.getElementById('trim').innerHTML = 'trim override: ' + value;
      }

      function tilt(value) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "tilt?tilt="+value, true);
        xhttp.send();
        document.getElementById('tilt').innerHTML = 'tilt override: ' + value;
      }

      function speed(value) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "speed?speed="+value, true);
        xhttp.send();
        document.getElementById('speed').innerHTML = 'speed: ' + (+Math.sqrt(Math.pow(2, value)).toFixed(2)) + 'x';
      }

      function delay(value) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "delay?delay="+value, true);
        xhttp.send();
        document.getElementById('delay').innerHTML = 'delay: ' + value;
      }
      
    </script>
</head>

<body>
    <div class="block">
        <div id="trim" class="sldLbl">trim</div>
        <input type="range" min="-90" max="90" value="0" class="slider" onchange="trim(this.value)" >

        <div id="tilt" class="sldLbl">tilt</div>
        <input type="range" min="-90" max="90" value="0" class="slider" onchange="tilt(this.value)" >

        <div id="speed" class="sldLbl">speed</div>
        <input type="range" min="-5" max="5" value="0" class="slider" oninput="speed(this.value)" >

      <!-- Uncomment to fine-tune your delay setting
        <div id="delay" class="sldLbl">delay</div>
        <input type="range" min="0" max="100" value="20" class="slider" onchange="delay(this.value)" >
      -->

    </div>
    <div class="block" style="margin-top: 42px;">
        <div class="btn cBDir dg" id="upLeft" onclick="fireCommand('upLeft')">↖</div>
        <div class="btn cBDir" id="run" onclick="fireCommand('run')">↑</div>
        <div class="btn cBDir dg" id="upRight" onclick="fireCommand('upRight')">↗</div>
        <div class="btn cBDir" id="turnL" onclick="fireCommand('turnL')">←</div>
        <div class="btn cBStop" id="stop" onclick="fireCommand('stop')">Stop</div>
        <div class="btn cBDir" id="turnR" onclick="fireCommand('turnR')">→</div>
        <div class="btn cBDir dg" id="backLeft" onclick="fireCommand('backLeft')">↙</div>
        <div class="btn cBDir" id="back" onclick="fireCommand('back')">↓</div>
        <div class="btn cBDir dg" id="backRight" onclick="fireCommand('backRight')">↘</div>
        <div class="btn cB" id="pushUps" onclick="fireCommand('pushUps')">Push Ups</div>
        <div class="btn cB" id="stretch" onclick="fireCommand('stretch')">Stretch</div>
        <div class="btn cB" id="dance" onclick="fireCommand('dance')">Dance</div>
        <div class="btn cB" id="jiggle" onclick="fireCommand('jiggle')">Jiggle</div>
        <div class="btn cB" id="moonWalk" onclick="fireCommand('moonWalk')">Moonwalk</div>
        <div class="btn cB" id="confused" onclick="fireCommand('confused')">Confused</div>
        <div class="btn cB" id="sayHi" onclick="fireCommand('sayHi')">Say Hi</div>
        <div class="btn cB" id="pack" onclick="fireCommand('pack')">Pack</div>
        <div class="btn cB" id="crawl" onclick="fireCommand('crawl')">Crawl</div>
        <div class="btn cB" id="tiptoe" onclick="fireCommand('tiptoe')">Tiptoe</div>
        <div class="btn cB" id="recover" onclick="fireCommand('recover')">Recover</div>
        <div class="btn cB" id="sit" onclick="fireCommand('sit')">Sit</div>
        <div class="btn cB" id="playDead" onclick="fireCommand('playDead')">Play Dead</div>
        <div class="btn cB" id="shiver" onclick="fireCommand('shiver')">Shiver</div>
        <div class="btn cB" id="scratchEar" onclick="fireCommand('scratchEar')">Scratch Ear</div>
        <div class="btn cB" id="pouncePrep" onclick="fireCommand('pouncePrep')">Pounce</div>
        <div class="btn cB" id="tapFoot" onclick="fireCommand('tapFoot')">Tap Foot</div>
        
        <div class="btn cBMgc" id="magic" onclick="fireCommand('magic')">Magic</div>
    </div>
</body>

</html>
)CPPHTML";

void WebConnector::handleRoot()
{
  Serial.println("send web ui");
  server.send(200, "text/html", page_html);
}

void WebConnector::handleCommand()
{
  String cmd = server.arg("command");
  Serial.println("command " + cmd);
  server.send(200, "text/plain", "OK");
  Mind::setActiveCommand(cmd);
}

void WebConnector::handleTrim()
{
  String trim = server.arg("trim");
  Serial.println("trim to " + trim);
  server.send(200, "text/plain", "OK");
  Mind::setHeightOverride(-trim.toInt());
}

void WebConnector::handleTilt()
{
  String tilt = server.arg("tilt");
  Serial.println("tilt to " + tilt);
  server.send(200, "text/plain", "OK");
  Mind::setTiltCorrection(-tilt.toInt());
}

void WebConnector::handleDelay()
{
  String delay = server.arg("delay");
  Serial.println("delay to " + delay);
  server.send(200, "text/plain", "OK");
  Mind::setDelay(delay.toInt());
}

void WebConnector::handleSpeed()
{
  float speed = sqrt(pow(2, server.arg("speed").toInt()));
  server.send(200, "text/plain", "OK");
  Mind::setSpeedModifier(speed);
}

void WebConnector::handleSpec()
{
  String body;
  if (server.hasArg("plain")) {
    body = server.arg("plain");
  } else if (server.hasArg("spec")) {
    body = server.arg("spec");
  }

  MoveSpec spec;
  if (body.length() > 0 && MoveSpec::fromJson(body, spec)) {
    Serial.println("[HTTP] Applied dynamic MoveSpec: " + spec.name);
    Mind::setDynamicSpec(spec);
    server.send(200, "text/plain", "OK");
  } else {
    Serial.println("[HTTP] Invalid MoveSpec JSON");
    server.send(400, "text/plain", "Invalid MoveSpec JSON");
  }
}

void WebConnector::init()
{
#if defined(WIFI_STA_SSID)
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_STA_SSID);
  WiFi.mode(WIFI_STA);

#if defined(WIFI_STA_PASS)
  if (strlen(WIFI_STA_PASS) > 0) {
    WiFi.begin(WIFI_STA_SSID, WIFI_STA_PASS);
  } else {
    WiFi.begin(WIFI_STA_SSID);
  }
#else
  WiFi.begin(WIFI_STA_SSID);
#endif

  // Wait up to 10 seconds (20 * 500ms) for connection
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("  IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("fairy")) {
      MDNS.addService("http", "tcp", 80);
      Serial.println("  mDNS responder started: http://fairy.local");
    }

#ifndef DISABLE_OTA
    ArduinoOTA.setHostname("fairy");
#if defined(OTA_PASSWORD)
    if (strlen(OTA_PASSWORD) > 0) {
      ArduinoOTA.setPassword(OTA_PASSWORD);
      Serial.println("  ArduinoOTA enabled: password protected");
    } else {
      Serial.println("  ArduinoOTA enabled: open LAN (no password)");
    }
#else
    Serial.println("  ArduinoOTA enabled: open LAN (no password)");
#endif

    ArduinoOTA.onStart([]() {
      String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
      Serial.println("\n[OTA] Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\n[OTA] Update complete. Rebooting...");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("[OTA] Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("[OTA] Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
    this->otaActive = true;
#endif
  } else {
    Serial.println();
    Serial.println("Failed to connect to Wi-Fi. Falling back to SoftAP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
    Serial.println("WiFi butterflies flying (SoftAP fallback)");
    Serial.print("  SSID: ");
    Serial.println(WiFi.softAPSSID());
    Serial.print("  IP: ");
    Serial.println(WiFi.softAPIP());
  }
#else
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid); // no password
  Serial.println("WiFi butterflies flying (SoftAP)");
  Serial.print("  SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("  IP: ");
  Serial.println(WiFi.softAPIP());
#endif

  server.on("/", handleRoot);
  server.on("/cmd", handleCommand);
  server.on("/trim", handleTrim);
  server.on("/tilt", handleTilt);
  server.on("/speed", handleSpeed);
  server.on("/delay", handleDelay);
  server.on("/spec", HTTP_POST, handleSpec);
  server.on("/spec", HTTP_GET, handleSpec);

  server.begin();
}

void WebConnector::handleConnection()
{
#if defined(WIFI_STA_SSID)
  MDNS.update();
#endif
#ifndef DISABLE_OTA
  if (this->otaActive) {
    ArduinoOTA.handle();
  }
#endif
  server.handleClient();
}

#endif // DISABLE_WIFI


