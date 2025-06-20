# 🧲 ESP32 Hall Effect Monitor

This project monitors magnetic fields using the ESP32's built-in Hall effect sensor. It provides real-time magnetic field detection with LED feedback and serial output, including calibration and threshold-based detection levels.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in `driver/adc.h` for ADC configuration

---

## ⚙️ Features

- Monitors magnetic field strength using ESP32's built-in Hall effect sensor
- Automatic sensor calibration on startup
- Three detection levels:
  - **Normal** – No significant magnetic field detected
  - **Field Detected** – Magnetic field above detection threshold
  - **STRONG MAGNETIC FIELD!** – Strong magnetic field detected
- Built-in LED (GPIO 2) provides visual feedback:
  - Solid ON – Ready/calibrated
  - Blinking – Field detected
  - Quick flash – Strong field detected
- Maintains a 60-sample history of readings
- Real-time serial output with status indicators

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field           | Description                                    |
|-----------------|------------------------------------------------|
| **Hall Value**  | Calibrated magnetic field reading (relative to baseline) |
| **Status**      | Detection level: Normal, Field Detected, or STRONG MAGNETIC FIELD! |

---

## ℹ️ About the ESP32 Hall Effect Sensor

- The ESP32 has a **built-in Hall effect sensor** that can detect magnetic fields.
- The sensor works by measuring the **voltage difference** between two ADC channels (ADC1_CHANNEL_0 and ADC1_CHANNEL_3).
- **Calibration:** The sensor automatically calibrates on startup to establish a baseline reading in the current environment.
- **Detection Thresholds:**
  - **Detection Threshold:** 100 (sensitive detection)
  - **Strong Threshold:** 500 (strong field detection)
- **How it works:** When a magnet approaches the ESP32, the Hall effect sensor detects the magnetic field and produces a voltage change that is converted to a digital reading.

**Learning Resources:**
- [ESP32 Technical Reference Manual - Hall Sensor](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [Hall Effect Sensor Basics (SparkFun)](https://learn.sparkfun.com/tutorials/hall-effect-sensor-hookup-guide)
- [ESP32 ADC and Hall Sensor (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)

---

## 🔧 Setup Instructions

1. Connect ESP32 via USB
2. Upload the `hall-monitor.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. Wait for calibration to complete (LED will be solid ON)
5. Bring magnets near the ESP32 to test magnetic field detection

---

## 📝 License

MIT License – free to use, modify, and share.