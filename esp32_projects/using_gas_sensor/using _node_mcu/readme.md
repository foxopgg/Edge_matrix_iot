# NodeMCU Gas Monitoring with MQ2 Sensor and Python Database Integration

This project demonstrates how to use a NodeMCU (ESP8266) microcontroller with an MQ2 gas sensor to monitor gas concentration and store the data in a local database using a Python script and XAMPP.

## Overview

- **Hardware:** NodeMCU ESP8266, MQ2 Gas Sensor
- **Software:** Arduino IDE (for ESP8266), Python, XAMPP (Apache, MySQL, PHP)
- **Functionality:** The NodeMCU reads gas concentration data from the MQ2 sensor and sends it over a serial connection to a Python script running on a local machine. The Python script parses the data and inserts it into a MySQL database managed by XAMPP.

## Workflow

1. **Sensor Reading:**  
   The MQ2 gas sensor is connected to the NodeMCU, which reads analog values representing gas concentration.

2. **Data Transmission:**  
   The NodeMCU sends the gas values via serial communication (USB) to a Python script.

3. **Python Receiver:**  
   A Python script on the local machine receives the serial data, determines the pollution level (Low, Medium, or High), and stores it in the MySQL database.

4. **Database Storage:**  
   XAMPP provides a MySQL database where all gas readings are stored along with harm level classifications and timestamps.

## Features

- Real-time gas level monitoring
- Classification into clean, medium, or high pollution levels
- Local database logging for further analysis
- Easy integration with dashboards or alert systems

## Applications

- Indoor air quality monitoring
- Fire and smoke detection (basic)
- Safety monitoring in industrial environments

## Requirements

- NodeMCU ESP8266 board
- MQ2 gas sensor
- Jumper wires and breadboard
- Arduino IDE with ESP8266 board support
- Python 3 with `mysql-connector-python`
- XAMPP with MySQL service running

## Example Database Table

```sql
CREATE TABLE gas_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    gas_value FLOAT,
    gas_harm_level VARCHAR(10),
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

## Pollution Level Thresholds

| Range         | Category         |
| ------------- | ---------------- |
| 100 – 300     | Clean Air (Low)  |
| 301 – 700     | Medium Pollution |
| 701 and above | High Pollution   |
