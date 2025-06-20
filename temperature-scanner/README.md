# ��️ ESP32 Temperature Scanner

This project reads the internal temperature sensor of an ESP32 board and displays the temperature in Celsius via the serial monitor. It also uses the onboard LED to indicate when a reading is taken.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in temperature sensor (no external library required)

---

## ⚙️ Features

- Reads the ESP32's internal temperature sensor
- Displays the following for each reading:
  - **Raw Value** – Direct sensor output
  - **Temperature (°C)** – Converted value in Celsius
- Built-in LED (GPIO 2) blinks with each reading

---

## ℹ️ About the ESP32 Internal Temperature Sensor

- The ESP32 has a built-in temperature sensor **inside the chip itself** (not a separate component on the board).
- The sensor is mainly for monitoring the chip's own temperature (for diagnostics/thermal management), **not for precise ambient temperature measurement**.
- The function `temprature_sens_read()` returns a **raw, uncalibrated 8-bit value** (0–255) that increases as the chip gets hotter.
- The raw value is converted to an approximate Celsius value using the formula: `float temp_c = (raw - 32) / 1.8;` (accuracy may vary between chips).
- **Limitations:**
  - The reading is affected by the chip's own heat and power consumption.
  - The sensor is **not factory-calibrated** for accurate room temperature.
  - For accurate ambient temperature, use an external sensor (e.g., DHT22, DS18B20).

**Learning Resources:**
- [ESP32 Technical Reference Manual (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [ESP32 Arduino Core: Internal Temperature Sensor](https://github.com/espressif/arduino-esp32/issues/1023)
- [External Temperature Sensors with ESP32 (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-temperature-sensor-lm35-ds18b20/)

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field         | Description                                      |
|---------------|--------------------------------------------------|
| **Raw**       | Raw value from the ESP32 internal sensor         |
| **Temp (°C)** | Calculated temperature in degrees Celsius        |

---

## 🔧 Setup Instructions

1. Connect ESP32 via USB
2. Upload the `temperature-scanner.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. View the temperature readings every 3 seconds

---

## 📝 License

MIT License – free to use, modify, and share. 