# 🎹 ESP32 Capacitive Touch Piano

This project creates a musical instrument using the ESP32's built-in capacitive touch sensors. It generates different musical tones when you touch the designated GPIO pins, creating a simple piano-like interface with visual LED feedback.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in `Arduino.h` (no external libraries required)

---

## ⚙️ Features

- **7 capacitive touch sensors** mapped to different GPIO pins
- **Pentatonic musical scale** for pleasant, harmonious sounds
- **Automatic sensor calibration** on startup
- **Visual LED feedback** with different patterns:
  - Breathing effect when idle
  - Blinking patterns when sensors are touched
  - Startup animation sequence
- **Serial output** showing touch events and sensor values
- **Built-in speaker output** via GPIO 25 for audio generation

---

## 🎵 Musical Notes

The piano uses a pentatonic scale (5-note scale) for harmonious sounds:

| Sensor | Note | Frequency (Hz) | GPIO Pin |
|--------|------|----------------|----------|
| 1      | C4   | 262            | GPIO 4   |
| 2      | D4   | 294            | GPIO 15  |
| 3      | E4   | 330            | GPIO 13  |
| 4      | G4   | 392            | GPIO 12  |
| 5      | A4   | 440            | GPIO 14  |
| 6      | B4   | 494            | GPIO 27  |
| 7      | C5   | 523            | GPIO 33  |

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field        | Description                                    |
|--------------|------------------------------------------------|
| **Sensor X touched!** | Indicates which touch sensor was activated |
| **Value: X** | Raw capacitive touch reading from the sensor |
| **Baseline: X** | Calibrated baseline value for each sensor |

---

## ℹ️ About ESP32 Capacitive Touch Sensors

- The ESP32 has **10 built-in capacitive touch sensors** (T0-T9) that can detect touch without physical contact.
- **How it works:** The sensors detect changes in capacitance when a conductive object (like your finger) approaches the GPIO pin.
- **Calibration:** The system automatically calibrates each sensor on startup to establish baseline readings.
- **Sensitivity:** Adjustable via `TOUCH_THRESHOLD` - lower values make sensors more sensitive.
- **GPIO Pins Used:** 4, 12, 13, 14, 15, 27, 33 (these are the capacitive touch-enabled pins).

**Learning Resources:**
- [ESP32 Touch Sensor Guide (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-touch-pins-arduino-ide/)
- [ESP32 Technical Reference - Touch Sensor](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [Capacitive Touch Sensor Basics](https://www.analog.com/en/analog-dialogue/articles/capacitive-sensing-with-mcu.html)

---

## 🔧 Setup Instructions

1. Connect ESP32 via USB
2. Upload the `capacitive-touch-piano.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. Wait for sensor calibration to complete
5. Touch the designated GPIO pins to generate musical tones
6. Watch the built-in LED for visual feedback

**Note:** For best results, connect a small speaker to GPIO 25 and GND for audio output.

---

## 📝 License

MIT License – free to use, modify, and share.
