#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  
  // Wait for serial connection with timeout
  unsigned long startTime = millis();
  while (!Serial && (millis() - startTime < 5000)) {
    // Wait for serial port to connect
  }
  
  Serial.println("Serial initialized!");
  pinMode(LED_PIN, OUTPUT);
  
  // Show we're starting
  Serial.println("\nTemperature Logger Started");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Only for original ESP32 chips
  #ifdef CONFIG_IDF_TARGET_ESP32
    uint8_t raw = temprature_sens_read();
    float temp_c = (raw - 32) / 1.8;
    
    Serial.printf("Raw: %d, Temp: %.2f°C\n", raw, temp_c);
  #else
    Serial.println("No temp sensor on this ESP model");
  #endif
  
  // Blink and wait
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(2900); // 3 second total delay
}