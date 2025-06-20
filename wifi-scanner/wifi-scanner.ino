#include "WiFi.h"

// Built-in LED configuration
#define LED_PIN 2
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize WiFi in station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("\nESP32 WiFi Scanner");
  Serial.println("------------------");
}

void loop() {
  // Start scanning - turn LED ON
  digitalWrite(LED_PIN, HIGH);
  Serial.println("\nScanning WiFi networks...");
  
  // Perform network scan
  int networksFound = WiFi.scanNetworks();
  
  // Scanning complete - turn LED OFF
  digitalWrite(LED_PIN, LOW);

  // Display results
  Serial.printf("%d networks found:\n", networksFound);
  Serial.println("------------------------------------------------");
  Serial.println(" SSID             | RSSI | CH | ENCRYPTION | MAC");
  Serial.println("------------------------------------------------");

  for (int i = 0; i < networksFound; i++) {
    // Print network details
    Serial.printf(" %-16s | %4d | %2d | %-10s | ",
                 WiFi.SSID(i).c_str(),
                 WiFi.RSSI(i),
                 WiFi.channel(i),
                 encryptionType(WiFi.encryptionType(i)));
    
    // Print MAC address
    uint8_t* bssid = WiFi.BSSID(i);
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
                 bssid[0], bssid[1], bssid[2],
                 bssid[3], bssid[4], bssid[5]);
  }

  // Wait before next scan
  delay(10000);
}

// Helper function to translate encryption type
const char* encryptionType(wifi_auth_mode_t type) {
  switch (type) {
    case WIFI_AUTH_OPEN: return "OPEN";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-E";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    default: return "UNKNOWN";
  }
}