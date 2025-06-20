# 📡 ESP32 WiFi Scanner

This project scans for nearby WiFi networks using an ESP32 board and displays detailed information for each network, such as SSID, signal strength (RSSI), channel, encryption type, and MAC address. It also uses the onboard LED to visually indicate when scanning is in progress.

---

## 🛠️ Project Details

- **Board:** ESP32 (tested on DevKit v1)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE or PlatformIO
- **Library Used:** Built-in `WiFi.h`

---

## ⚙️ Features

- Scans for all nearby WiFi networks
- Displays the following for each:
  - **SSID** – Network name
  - **RSSI** – Signal strength (in dBm)
  - **Channel** – Frequency channel used
  - **Encryption** – Type of WiFi security
  - **MAC Address** – Unique hardware address (partially redacted for privacy)
- Built-in LED (GPIO 2) lights up during scan

---

## 🖥️ Sample Serial Output
![Serial Monitor](<./images/Results.png>)

---

## 📘 Explanation of Output

| Field        | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| **SSID**     | The network name broadcast by the WiFi router.                             |
| **RSSI**     | Received Signal Strength Indicator in dBm. Ranges from `-30` (excellent) to `-90+` (very weak). |
| **Channel**  | The frequency lane used by the WiFi network. Helps prevent interference.   |
| **Encryption** | Security protocol used: `OPEN`, `WEP`, `WPA`, `WPA2`, `WPA3`, etc.       |
| **MAC Address** | Unique hardware address of the router. Partially redacted for privacy. |

---

### 📊 RSSI (Signal Strength) Reference

| RSSI Value   | Signal Strength | Quality       |
|--------------|------------------|----------------|
| -30 dBm      | Excellent         | 🔋 Full bars    |
| -50 to -60   | Very Good         | 👍 Stable       |
| -70          | OK                | ⚠️ Moderate     |
| -80          | Weak              | ❌ Unstable     |
| -90 or below | Very Weak         | 🚫 Unusable     |

---

### 📡 WiFi Channels Quick Info

- **2.4 GHz** band has channels from **1 to 14**
- Most used channels are **1, 6, and 11** (they don't overlap)
- **5 GHz** band has many more channels, less interference

Your ESP32 will report the active channel of each network, which is useful for optimizing WiFi performance or doing spectrum analysis.

---

## 🔧 Setup Instructions

1. Connect ESP32 via USB
2. Upload the `wifi-scanner.ino` using Arduino IDE
3. Open Serial Monitor at `115200` baud
4. View the scanned WiFi networks every 10 seconds

---

## 📝 License

MIT License – free to use, modify, and share.