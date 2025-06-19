import serial
import mysql.connector
from datetime import datetime

# Setup serial connection (adjust 'COM5' as needed)
ser = serial.Serial('COM5', 115200)

# Connect to MySQL database
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="esp_logger"
)

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

print("Listening for gas sensor data...")

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()
        if line:
            try:
                gas_value = float(line)
                print(f"Gas Value: {gas_value}")

                # Determine harm level
                if 100 <= gas_value <= 300:
                    harm_level = "low"
                elif 300 < gas_value <= 700:
                    harm_level = "medium"
                elif gas_value > 700:
                    harm_level = "high"
                else:
                    harm_level = "none"

                # Insert both values in one query
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
