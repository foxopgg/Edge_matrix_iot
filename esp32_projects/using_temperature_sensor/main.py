import serial
import mysql.connector
from datetime import datetime

# Serial port (Check from Device Manager: COM3, COM5, etc.)
ser = serial.Serial('COM5', 115200)  # Update COM port if needed

# Connect to MySQL database
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="temp_logger"
)

cursor = conn.cursor()

# Create table (run only once)
cursor.execute("""
CREATE TABLE IF NOT EXISTS temperature_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperature FLOAT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")

print("Listening for temperature data...")

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()
        if line:
            # Only process if line can be converted to float
            try:
                temperature = float(line)
                print(f"Temperature: {temperature} °C")

                cursor.execute("INSERT INTO temperature_data (temperature) VALUES (%s)", (temperature,))
                conn.commit()
            except ValueError:
                print(f"Ignored non-temp data: {line}")
    except Exception as e:
        print("Error:", e)
        break

ser.close()
conn.close()