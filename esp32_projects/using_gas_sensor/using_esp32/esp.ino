#define GAS_SENSOR_PIN 34  // Use ADC-capable pin like 32–39

void setup() {
  Serial.begin(115200);  // Start serial communication
}

void loop() {
  int gasValue = analogRead(GAS_SENSOR_PIN);  // Read raw analog value (0–4095)
  float voltage = gasValue * (3.3 / 4095.0);   // Convert to voltage (0–3.3V)

//  Serial.print("Gas Sensor Value: ");
  Serial.print(gasValue);
//  Serial.print(" | Voltage: ");
//  Serial.print(voltage, 3);  // Show 3 decimal places
//  Serial.println(" V");

  delay(10000);  // 10-second delay
}
