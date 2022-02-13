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
            background-color: orange;
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
        <div class="cB" id="pushup" onclick="fireCommand('pushUp')">Push Up</div>
        <div class="cBDir" id="run" onclick="fireCommand('run')">Run</div>
        <div class="cB" id="upDown" onclick="fireCommand('upDown')">Up Down</div>
        <div class="cBDir" id="turnL" onclick="fireCommand('turnL')">Left</div>
        <div class="cBStop" id="stop" onclick="fireCommand('stop')">Stop</div>
        <div class="cBDir" id="turnR" onclick="fireCommand('turnR')">Right</div>
        <div class="cB" id="hello" onclick="fireCommand('hello')">Hello</div>
        <div class="cBDir" id="frontBack" onclick="fireCommand('frontBack')">Back</div>
        <div class="cB" id="jump" onclick="fireCommand('jump')">Jump</div>
        <div class="cB" id="dance" onclick="fireCommand('dance')">Dance</div>
        <div class="cB" id="frontBack" onclick="fireCommand('upDfrontBackown')">Front Back</div>
        <div class="cB" id="auto" onclick="fireCommand('auto')">Auto</div>
        <div class="cB" id="moonWalk" onclick="fireCommand('moonWalk')">Moonwalk</div>
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
