#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Server";       // Name of server ESP32's AP
const char* password = "12345678";       // Password of AP
const char* serverIP = "192.168.4.1";    // Replace with ESP32 #2 IP
const int mq2Pin = 34;                   // MQ2 connected to GPIO34

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ESP32 Server AP");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP!");
  Serial.print("Client IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int mq2Value = analogRead(mq2Pin); // Read analog value from MQ2
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Construct URL with sensor value
    String url = "http://" + String(serverIP) + "/update?mq2=" + String(mq2Value);
    http.begin(url);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Server Response: " + payload);
    } else {
      Serial.println("Error sending request");
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected!");
  }

  delay(2000); // Send every 2 seconds
}
