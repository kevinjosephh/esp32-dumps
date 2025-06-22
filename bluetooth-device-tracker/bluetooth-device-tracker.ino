#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

// BLE Scanning
BLEScan* pBLEScan;
const int SCAN_DURATION = 4; // Scan duration in seconds
unsigned long lastScanTime = 0;
const long SCAN_INTERVAL = 5000; // 5 seconds between scans

void setup() {
  Serial.begin(115200);
  Serial.println("\nESP32 BLE Scanner");
  Serial.println("=================");
  
  // Initialize BLE
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true); // Active scan for more accurate RSSI
  
  Serial.println("BLE initialized. Starting scans...");
  Serial.println("----------------------------------");
}

void loop() {
  if (millis() - lastScanTime > SCAN_INTERVAL) {
    scanDevices();
    lastScanTime = millis();
  }
  delay(10);
}

void scanDevices() {
  Serial.println("\nScanning for BLE devices...");
  
  // Perform BLE scan
  BLEScanResults* results = pBLEScan->start(SCAN_DURATION, false);
  
  Serial.println("\n===== Scan Results =====");
  Serial.printf("Found %d device(s)\n", results->getCount());
  
  if (results->getCount() > 0) {
    Serial.println("-----------------------------------");
    Serial.println("Device Name         RSSI  Distance");
    Serial.println("-----------------------------------");
    
    for (int i = 0; i < results->getCount(); i++) {
      BLEAdvertisedDevice device = results->getDevice(i);
      String name = device.getName().c_str();
      if (name.length() == 0) name = "Unknown";
      
      int rssi = device.getRSSI();
      String distance = getDistance(rssi);
      
      // Format output with fixed widths
      char output[50];
      snprintf(output, sizeof(output), "%-18s %4ddBm  %s", 
               name.substring(0, 17).c_str(), rssi, distance.c_str());
      
      Serial.println(output);
    }
  }
  
  Serial.println("===================================");
  
  // Clean up scan results
  pBLEScan->clearResults();
  delete results;
}

String getDistance(int rssi) {
  if (rssi > -50) return "<1m   ";
  if (rssi > -65) return "1-3m  ";
  if (rssi > -80) return "3-10m ";
  if (rssi > -95) return "10-20m";
  return ">20m  ";
}