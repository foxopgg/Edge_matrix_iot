#include <WiFi.h>
#include <WebServer.h>

// Create Access Point credentials
const char* ssid = "ESP32-Server";
const char* password = "12345678";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32 Server");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // Save this for client

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
