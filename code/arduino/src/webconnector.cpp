#include "webconnector.h"

const char* ssid = "MINIKAME";
// const char* password = "asdf";

ESP8266WebServer server(80);
String WebConnector::activeCommand = "home";

const char * page_html = R"CPPHTML(
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
        <div class="cB" id="stretch" onclick="fireCommand('stretch')">Stretch</div>
        <div class="cB" id="dance" onclick="fireCommand('dance')">Dance</div>
        <div class="cB" id="jiggle" onclick="fireCommand('jiggle')">Jiggle</div>
        <div class="cB" id="moonWalk" onclick="fireCommand('moonWalk')">Moonwalk</div>
        <div class="cB" id="confused" onclick="fireCommand('confused')">Confused</div>
        
        <div class="cBMgc" id="magic" onclick="fireCommand('magic')">Magic</div>
    </div>
</body>

</html>
)CPPHTML";


void WebConnector::handleRoot() {
  Serial.println("handle root...");
  server.send(200, "text/html", page_html);
}

void WebConnector::handleCommand() {
  String cmd = server.arg("command");
  Serial.println("handle command... " + cmd);
  server.send(200);
  activeCommand = cmd;
}

void WebConnector::init() {
  delay(1000);
  // WiFi.softAP(ssid, password);
  WiFi.softAP(ssid); // no password
  
  server.on("/", handleRoot);
  
  server.on("/cmd", handleCommand);

  server.begin();

  Serial.println("WiFi started");
  Serial.println(WiFi.softAPSSID());
  Serial.println(WiFi.softAPIP());
}

void WebConnector::handleConnection() {
  server.handleClient();
}

String WebConnector::getActiveCommand() {
  return activeCommand;
}
