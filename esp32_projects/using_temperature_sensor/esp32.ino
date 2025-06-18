#define TEMP_PIN 34  // Analog input pin

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // ESP32 has 12-bit ADC by default (0–4095)
}

void loop() {
  int analogValue = analogRead(TEMP_PIN);

  // Convert analog value to voltage
  float voltage = analogValue * (3.3 / 4095.0);

  // Assuming LM35-like sensor: 10mV per °C
  float temperatureC = voltage * 100;
//
//  Serial.print("Analog: ");
//  Serial.print(analogValue);
//  Serial.print(" | Voltage: ");
//  Serial.print(voltage);
//  Serial.print(" V | Temperature: ");
  Serial.print(temperatureC);
  Serial.println("\n");

  delay(10000);
}