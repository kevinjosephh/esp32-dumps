# 📱 ESP32 Bluetooth Device Tracker

This project scans for nearby Bluetooth Low Energy (BLE) devices using the ESP32's built-in Bluetooth capabilities. It displays device names, signal strength (RSSI), and estimated distances, providing real-time tracking of BLE devices in the vicinity.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in `BLEDevice.h`, `BLEUtils.h`, `BLEScan.h`

---

## ⚙️ Features

- Scans for nearby Bluetooth Low Energy (BLE) devices
- Displays the following for each device:
  - **Device Name** – BLE device name (or "Unknown" if not available)
  - **RSSI** – Signal strength in dBm
  - **Distance** – Estimated distance based on signal strength
- Active scanning for more accurate RSSI readings
- Automatic scanning every 5 seconds
- 4-second scan duration per cycle
- Clean, formatted output with fixed-width columns

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field        | Description                                    |
|--------------|------------------------------------------------|
| **Device Name** | BLE device name (truncated to 17 characters) |
| **RSSI**     | Received Signal Strength Indicator in dBm    |
| **Distance** | Estimated distance based on RSSI values       |

---

## ℹ️ About BLE Scanning and Distance Estimation

- **BLE (Bluetooth Low Energy)** is a wireless technology for short-range communication.
- **RSSI (Received Signal Strength Indicator)** measures the power level of received signals.
- **Distance Estimation** is based on RSSI values:
  - **<1m** – Very close (RSSI > -50 dBm)
  - **1-3m** – Close proximity (RSSI -50 to -65 dBm)
  - **3-10m** – Medium range (RSSI -65 to -80 dBm)
  - **10-20m** – Long range (RSSI -80 to -95 dBm)
  - **>20m** – Very far (RSSI < -95 dBm)

**Note:** Distance estimation is approximate and can be affected by:
- Physical obstacles (walls, furniture)
- Device orientation
- Environmental interference
- Device power settings

**Learning Resources:**
- [ESP32 Bluetooth Guide (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/)

---

## �� Setup Instructions

1. Connect ESP32 via USB
2. Upload the `bluetooth-device-tracker.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. View BLE device scans every 5 seconds
5. Bring BLE devices (phones, smartwatches, etc.) near the ESP32 to test

---

## 📝 License

MIT License – free to use, modify, and share.