#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ESP8266-Server";
const char* password = "12345678";
const char* serverIP = "192.168.4.1";  // Replace with your server IP
const int mq2Pin = A0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to AP");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP");
  Serial.print("Client IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int mq2Value = analogRead(mq2Pin);
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;  // ✅ New requirement
    HTTPClient http;

    String url = "http://" + String(serverIP) + "/update?mq2=" + String(mq2Value*6);
    http.begin(client, url);  // ✅ Fixed function

    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Server Response: " + payload);
    } else {
      Serial.println("Error sending request");
    }

    http.end();
  }

  delay(2000);  // Delay before next reading
}
