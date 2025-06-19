import serial
import mysql.connector
from datetime import datetime

# Setup serial connection (adjust COM port as needed, e.g., 'COM5' on Windows or '/dev/ttyUSB0' on Linux)
ser = serial.Serial('COM5', 115200, timeout=2)

# Connect to MySQL database
try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="esp_logger"
    )
except mysql.connector.Error as err:
    print(f"Database connection failed: {err}")
    exit()

cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute("""
CREATE TABLE IF NOT EXISTS gas_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    gas_value FLOAT,
    gas_harm_level VARCHAR(10),
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")

print("Listening for gas sensor data from ESP32...")

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()
        if line:
            try:
                gas_value = float(line)

                # Determine harm level
                if 0 <= gas_value <= 1000:
                    harm_level = "low"
                elif 1000 < gas_value <= 3000:
                    harm_level = "medium"
                elif gas_value > 3000:
                    harm_level = "high"
                else:
                    harm_level = "none"

                # Print to console
                print(f"Gas Value: {gas_value} | Harm Level: {harm_level}")

                # Insert data into MySQL
                cursor.execute(
                    "INSERT INTO gas_data (gas_value, gas_harm_level) VALUES (%s, %s)",
                    (gas_value, harm_level)
                )
                conn.commit()
            except ValueError:
                print(f"Ignored invalid data: {line}")
    except Exception as e:
        print("Error:", e)
        break

ser.close()
conn.close()
