# ♻️ Smart IoT Waste Bin (Grace X Project)

This is the official repository for the Smart Waste Bin project developed by **Team Grace X** from Grace High School. The project combines embedded systems, IoT, and real-time data monitoring to promote smarter, cleaner cities in line with **SDG Goals 9, 11, 12, and 13**.

## 🌟 Features

- 🔊 Motion-activated lid using a PIR sensor
- 📏 Fill level detection using an ultrasonic sensor
- 🚦 LED indicators (red, yellow, green) for fill status
- 📲 Real-time updates sent to Blynk Cloud (via NodeMCU)
- ⚙️ Manual toggle switch for power control with 9V
- 🪫 AMS1117-3.3V voltage regulation for safe NodeMCU powering

---

## 🧠 How It Works

The system uses two microcontrollers:

1. **Arduino Uno**: Handles sensors, servo motor, LEDs, and logic
2. **NodeMCU (ESP8266)**: Reads serial data from Arduino and uploads it to Blynk Cloud

---

## 📡 Data Sent to Blynk

| Data Type        | Virtual Pin | Description                      |
|------------------|-------------|----------------------------------|
| Fill Level (%)   | V0          | Ultrasonic sensor reading        |
| Motion Status    | V1          | "DETECTED" or "NOT DETECTED"     |
| Connection Flag  | V2          | 1 (connected), 0 (offline)       |

---

## 📦 Folder Structure

