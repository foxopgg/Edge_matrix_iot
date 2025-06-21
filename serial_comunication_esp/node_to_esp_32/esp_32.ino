#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Server";
const char* password = "12345678";

WebServer server(80);

const int relayPin = 26;  // GPIO pin connected to relay

void handleUpdate() {
  if (server.hasArg("mq2")) {
    String mq2Str = server.arg("mq2");
    int mq2Val = mq2Str.toInt();
    Serial.println("Received MQ2 value: " + String(mq2Val));

    // Trigger relay if gas level is medium
    if (mq2Val >= 500 && mq2Val <= 1000) {
      digitalWrite(relayPin, LOW);  // Activate relay
      Serial.println("Relay ON (Medium gas level)");
    } else {
      digitalWrite(relayPin, HIGH); // Deactivate relay
      Serial.println("Relay OFF");
    }

    server.send(200, "text/plain", "MQ2 value received: " + mq2Str);
  } else {
    server.send(400, "text/plain", "Missing 'mq2' parameter");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay OFF by default

  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/update", handleUpdate);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}
