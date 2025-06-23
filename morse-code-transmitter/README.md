# 📡 ESP32 Morse Code Transmitter

This project creates a Morse code receiver using the ESP32's capacitive touch sensor. It decodes Morse code input (dots and dashes) into alphanumeric characters in real-time, making it perfect for learning Morse code or creating a simple communication system.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in `Arduino.h` (no external libraries required)

---

## ⚙️ Features

- **Real-time Morse code decoding** from capacitive touch input
- **Supports A-Z and 0-9** characters using standard Morse code
- **Visual LED feedback** during touch input
- **Automatic timing detection:**
  - Short press = DOT (.)
  - Long press = DASH (-)
  - Automatic letter and word spacing
- **Smoothed touch reading** using averaged samples for reliability
- **Serial output** showing dots/dashes and decoded characters
- **Debounce protection** to prevent false readings

---

## 📡 Morse Code Timing

| Input Type | Duration | Description |
|------------|----------|-------------|
| **DOT (.)** | < 300ms | Short press on GPIO4 |
| **DASH (-)** | ≥ 300ms | Long press on GPIO4 |
| **Letter Gap** | 400ms | Time between symbols in a letter |
| **Word Gap** | 1200ms | Time between different words |

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field        | Description                                    |
|--------------|------------------------------------------------|
| **.** or **-** | Shows dots and dashes as they're input |
| **-> X** | Decoded character (A-Z or 0-9) |
| **[Invalid: ...]** | Invalid Morse sequence |

---

## ℹ️ About Morse Code and ESP32 Touch Input

- **Morse Code** is a method of transmitting text using standardized sequences of dots (.) and dashes (-).
- **Touch Input:** Uses the ESP32's capacitive touch sensor on GPIO4 (T0) to detect presses.
- **Timing Detection:** The system automatically distinguishes between dots and dashes based on press duration.
- **Character Support:** Includes all 26 letters (A-Z) and 10 digits (0-9) using standard Morse code.
- **Averaged Reading:** Uses 5-sample averaging to reduce noise and improve reliability.

**Common Morse Code Examples:**
- **SOS:** ... --- ... (3 dots, 3 dashes, 3 dots)
- **HELLO:** .... . .-.. .-.. ---
- **123:** .---- ..--- ...--

**Learning Resources:**
- [ESP32 Touch Sensor Guide](https://randomnerdtutorials.com/esp32-touch-pins-arduino-ide/)
- [International Morse Code Standard](https://www.itu.int/rec/R-REC-M.1677-1-200910-I/en)

---

## 🔧 Setup Instructions

1. Connect ESP32 via USB
2. Upload the `morse-code-transmitter.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. Touch GPIO4 pin to input Morse code:
   - **Short press** (< 300ms) = DOT (.)
   - **Long press** (≥ 300ms) = DASH (-)
5. Wait for automatic character decoding
6. Watch the built-in LED for visual feedback during input

---

## 📝 License

MIT License – free to use, modify, and share.
