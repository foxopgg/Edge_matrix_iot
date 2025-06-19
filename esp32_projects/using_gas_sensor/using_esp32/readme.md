# ESP32 Gas Monitoring with MQ2 Sensor and Python Database Integration

This project demonstrates how to use an **ESP32 microcontroller** with an **MQ2 gas sensor** to monitor gas concentration and store the data in a local MySQL database using a **Python script and XAMPP**.

---

## 🔧 Overview

- **Hardware:** ESP32, MQ2 Gas Sensor  
- **Software:** Arduino IDE (for ESP32), Python, XAMPP (Apache, MySQL, PHP)  
- **Functionality:**  
  The ESP32 reads analog values from the MQ2 sensor and sends them via serial to a Python script running on a local PC. The script categorizes the gas level and stores the information in a MySQL database managed by XAMPP.

---

## 🚦 Workflow

1. **Sensor Reading**  
   The MQ2 gas sensor is connected to an ADC-capable pin on the ESP32 (e.g., GPIO34). The ESP32 reads analog values representing gas concentration.

2. **Data Transmission**  
   The ESP32 sends the analog value to the PC via USB serial.

3. **Python Receiver**  
   A Python script reads the serial data, classifies the gas level as `low`, `medium`, or `high`, and logs the information to a MySQL database.

4. **Database Storage**  
   A MySQL table (`gas_data`) stores gas values, timestamps, and harm level classifications.

---

## ✅ Features

- Real-time gas level monitoring  
- Pollution level classification  
- Local database logging for analysis or dashboard integration  
- Easy to extend with alerts (email, buzzer, etc.)

---

## ⚙️ Requirements

- ESP32 development board  
- MQ2 gas sensor  
- Jumper wires and breadboard  
- Arduino IDE with ESP32 board support  
- Python 3 with `mysql-connector-python`  
- XAMPP with MySQL service running  
- Serial USB connection to PC

---

## 🗄️ Example MySQL Table

```sql
CREATE TABLE gas_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    gas_value FLOAT,
    gas_harm_level VARCHAR(10),
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
