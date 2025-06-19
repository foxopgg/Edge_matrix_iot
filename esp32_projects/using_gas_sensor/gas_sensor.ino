#define GAS_SENSOR_PIN A0  // NodeMCU has one analog pin (A0)

void setup() {
  Serial.begin(115200);  // Initialize serial communication
}

void loop() {
  int gasValue = analogRead(GAS_SENSOR_PIN);  // Read analog gas value

  // Print raw analog value (0–1023 for ESP8266)
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Add delay before next reading
  delay(10000);  // 10 seconds
}
