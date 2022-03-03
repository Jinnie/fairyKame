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
        div {
            width: 100%;
            height: 400px;
        }

        div div {
            width: 33%;
            height: 33%;
            outline: 1px solid;
            float: left;
            font-size: 24px;
            color: white;
            text-align: center;
            line-height: 500%;
        }

        .cB {
            background-color: blue;
        }

        .cBStop {
            background-color: red;
        }

        .cBDir {
            font-size: 40px;
            line-height: 300%;
            background-color: orange;
        }
        .cBDir.dg {
            background-color: blue;
        }
        .cBMgc {
            background-color: green;
            width: 99%;
        }

        #trim, #tilt {
            color: white;
            float: right;
            font-size: 25px;
            margin-right: 1%;
        }

        .slider {
          -webkit-appearance: none;
          width: 99%;
          height: 50px;
          background: #e3e3e3;
          outline: none;
          -webkit-transition: .2s;
          transition: opacity .2s;
          margin-top: 25px;
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
      
    </script>
</head>

<body>
    <div>
        <div class="cBDir dg" id="upLeft" onclick="fireCommand('upLeft')">↖</div>
        <div class="cBDir" id="run" onclick="fireCommand('run')">↑</div>
        <div class="cBDir dg" id="upRight" onclick="fireCommand('upRight')">↗</div>
        <div class="cBDir" id="turnL" onclick="fireCommand('turnL')">←</div>
        <div class="cBStop" id="stop" onclick="fireCommand('stop')">Stop</div>
        <div class="cBDir" id="turnR" onclick="fireCommand('turnR')">→</div>
        <div class="cBDir dg" id="backLeft" onclick="fireCommand('backLeft')">↙</div>
        <div class="cBDir" id="back" onclick="fireCommand('back')">↓</div>
        <div class="cBDir dg" id="backRight" onclick="fireCommand('backRight')">↘</div>
        <div class="cB" id="pushUps" onclick="fireCommand('pushUps')">Push Ups</div>
        <div class="cB" id="stretch" onclick="fireCommand('stretch')">Stretch</div>
        <div class="cB" id="dance" onclick="fireCommand('dance')">Dance</div>
        <div class="cB" id="jiggle" onclick="fireCommand('jiggle')">Jiggle</div>
        <div class="cB" id="moonWalk" onclick="fireCommand('moonWalk')">Moonwalk</div>
        <div class="cB" id="confused" onclick="fireCommand('confused')">Confused</div>
        
        <div class="cBMgc" id="magic" onclick="fireCommand('magic')">Magic</div>

        <input type="range" min="-90" max="90" value="0" class="slider" onchange="trim(this.value)" >
        <p id="trim"></p>

        <input type="range" min="-90" max="90" value="0" class="slider" onchange="tilt(this.value)" >
        <p id="tilt"></p>
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

void WebConnector::init()
{
  // WiFi.softAP(ssid, password);
  WiFi.softAP(ssid); // no password

  server.on("/", handleRoot);

  server.on("/cmd", handleCommand);

  server.on("/trim", handleTrim);
  
  server.on("/tilt", handleTilt);

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
