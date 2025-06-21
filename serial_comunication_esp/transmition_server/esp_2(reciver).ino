#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Server";
const char* password = "12345678";

// Replace with actual server IP printed from server
const char* serverIP = "192.168.4.1";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Server...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://" + String(serverIP));
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Server Response: ");
      Serial.println(payload);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected!");
  }

  delay(2000);  // Send every 2 seconds
}
