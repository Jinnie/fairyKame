#include "webconnector.h"

const char *ssid = "MINIKAME";
// const char* password = "asdf";

ESP8266WebServer server(80);
String WebConnector::activeCommand = "stop";

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
        <input type="range" min="-5" max="5" value="0" class="slider" onchange="speed(this.value)" >

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
  server.send(200);
  activeCommand = cmd;
}

void WebConnector::handleTrim()
{
  String trim = server.arg("trim");
  Serial.println("trim to " + trim);
  server.send(200);
  Mind::setHeightOverride(-trim.toInt());
}

void WebConnector::handleTilt()
{
  String tilt = server.arg("tilt");
  Serial.println("tilt to " + tilt);
  server.send(200);
  Mind::setTiltCorrection(-tilt.toInt());
}

void WebConnector::handleDelay()
{
  String delay = server.arg("delay");
  Serial.println("delay to " + delay);
  server.send(200);
  Mind::setDelay(delay.toInt());
}

void WebConnector::handleSpeed()
{
  float speed = sqrt(pow(2, server.arg("speed").toInt()));
  server.send(200);
  Mind::setSpeedModifier(speed);
}

void WebConnector::init()
{
  // WiFi.softAP(ssid, password);
  WiFi.softAP(ssid); // no password

  server.on("/", handleRoot);

  server.on("/cmd", handleCommand);

  server.on("/trim", handleTrim);
  
  server.on("/tilt", handleTilt);
  
  server.on("/speed", handleSpeed);

  server.on("/delay", handleDelay);

  server.begin();

  Serial.println("WiFi started");
  Serial.println(WiFi.softAPSSID());
  Serial.println(WiFi.softAPIP());
}

void WebConnector::handleConnection()
{
  server.handleClient();
}

String WebConnector::getActiveCommand()
{
  return activeCommand;
}
