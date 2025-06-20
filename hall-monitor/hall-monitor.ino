#include <driver/adc.h>

#define LED_BUILTIN 2  // Built-in LED for status indication

// Magnetic field history
const int HISTORY_SIZE = 60;
int hallHistory[HISTORY_SIZE];
int historyIndex = 0;

// Detection thresholds
const int DETECTION_THRESHOLD = 100;
const int STRONG_THRESHOLD = 500;

// Hall sensor baseline
int baseline = 0;

// Custom Hall sensor reading function
int readHallSensor() {
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
  int val1 = adc1_get_raw(ADC1_CHANNEL_0);
  int val2 = adc1_get_raw(ADC1_CHANNEL_3);
  return val1 - val2;
}

void calibrateSensor() {
  Serial.println("Calibrating Hall sensor...");
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += readHallSensor();
    delay(10);
  }
  baseline = sum / 100;
  Serial.printf("Calibrated baseline: %d\n", baseline);
}

int readHall() {
  return readHallSensor() - baseline;
}

void printStatus(int value) {
  Serial.print("Hall Value: ");
  Serial.print(value);
  
  if (abs(value) > STRONG_THRESHOLD) {
    Serial.print(" | STRONG MAGNETIC FIELD!");
  } else if (abs(value) > DETECTION_THRESHOLD) {
    Serial.print(" | Field Detected");
  } else {
    Serial.print(" | Normal");
  }
  
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Flash LED to indicate startup
  for(int i=0; i<5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, HIGH); // Solid on = ready
  
  Serial.println("\nESP32 Hall Effect Monitor - Serial Mode");
  
  // Initialize history
  for (int i = 0; i < HISTORY_SIZE; i++) {
    hallHistory[i] = 0;
  }
  
  // Calibrate sensor
  calibrateSensor();
  
  Serial.println("Monitoring magnetic field...");
  Serial.println("Bring magnets near the ESP32 to test");
  Serial.println("----------------------------------");
}

void loop() {
  // Read Hall sensor and update history
  int hallValue = readHall();
  hallHistory[historyIndex] = hallValue;
  historyIndex = (historyIndex + 1) % HISTORY_SIZE;
  
  // Print status to serial
  printStatus(hallValue);
  
  // Simple LED feedback
  if (abs(hallValue) > STRONG_THRESHOLD) {
    digitalWrite(LED_BUILTIN, LOW); // Turn off during strong field
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (abs(hallValue) > DETECTION_THRESHOLD) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink
  }
  
  delay(500);
}