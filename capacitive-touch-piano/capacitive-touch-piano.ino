#include <Arduino.h>

// Built-in LED pin (red)
const int LED_BUILTIN = 2;      // Typically GPIO2 for most ESP32 boards

// Touch sensor pins (capacitive touch)
const int TOUCH_PIN1 = 4;       // T0 (GPIO4)
const int TOUCH_PIN2 = 15;      // T3 (GPIO15)
const int TOUCH_PIN3 = 13;      // T4 (GPIO13)
const int TOUCH_PIN4 = 12;      // T5 (GPIO12)
const int TOUCH_PIN5 = 14;      // T6 (GPIO14)
const int TOUCH_PIN6 = 27;      // T7 (GPIO27)
const int TOUCH_PIN7 = 33;      // T8 (GPIO33)

// Touch thresholds (adjust based on your environment)
const int TOUCH_THRESHOLD = 20; // Lower value = more sensitive

// Note frequencies (Pentatonic scale for pleasant sounds)
const int NOTES[] = {
  262,  // C4
  294,  // D4
  330,  // E4
  392,  // G4
  440,  // A4
  494,  // B4
  523   // C5
};

// Touch sensor state tracking
bool touchStates[7] = {false};
int touchBaselines[7] = {0};

// Timing variables
unsigned long lastTouchTime = 0;
unsigned long lastBlinkTime = 0;
bool ledState = LOW;
int blinkPattern = 0;

void setup() {
  Serial.begin(115200);
  
  // Configure LED pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Set up capacitive touch sensors
  Serial.println("\nESP32 Touch Tone Generator");
  Serial.println("==========================");
  Serial.println("Calibrating touch sensors...");
  
  // Calibrate touch sensors
  for (int i = 0; i < 7; i++) {
    // Take 10 readings to establish baseline
    int baseline = 0;
    for (int j = 0; j < 10; j++) {
      baseline += touchRead(getTouchPin(i));
      delay(10);
    }
    touchBaselines[i] = baseline / 10;
    Serial.printf("Sensor %d baseline: %d\n", i+1, touchBaselines[i]);
  }
  
  Serial.println("Calibration complete!");
  Serial.println("Touch the sensors to generate tones...");
  
  // Show startup sequence
  startupAnimation();
}

void loop() {
  // Read all touch sensors
  bool anyTouched = false;
  
  for (int i = 0; i < 7; i++) {
    int touchPin = getTouchPin(i);
    int touchValue = touchRead(touchPin);
    
    // Check if touched (value drops below baseline - threshold)
    bool touched = (touchValue < (touchBaselines[i] - TOUCH_THRESHOLD));
    
    // Detect touch state changes
    if (touched && !touchStates[i]) {
      // Touch started
      touchStates[i] = true;
      playTone(i);
      Serial.printf("Sensor %d touched! Value: %d\n", i+1, touchValue);
      lastTouchTime = millis();
      
      // Set blink pattern based on sensor
      blinkPattern = i + 1;
    } else if (!touched && touchStates[i]) {
      // Touch ended
      touchStates[i] = false;
    }
    
    anyTouched = anyTouched || touched;
  }
  
  // Update LED feedback
  updateLED(anyTouched);
  
  // Small delay to prevent flickering
  delay(10);
}

// Map sensor index to physical pin
int getTouchPin(int index) {
  switch(index) {
    case 0: return TOUCH_PIN1;
    case 1: return TOUCH_PIN2;
    case 2: return TOUCH_PIN3;
    case 3: return TOUCH_PIN4;
    case 4: return TOUCH_PIN5;
    case 5: return TOUCH_PIN6;
    case 6: return TOUCH_PIN7;
    default: return TOUCH_PIN1;
  }
}

// Play a tone when a sensor is touched
void playTone(int sensorIndex) {
  // Generate tone using the ESP32's built-in tone() function
  int freq = NOTES[sensorIndex];
  tone(25, freq, 200);  // GPIO25, frequency, duration 200ms
}

// Update LED feedback based on activity
void updateLED(bool touched) {
  unsigned long currentTime = millis();
  
  // If recently touched, use blink pattern
  if (touched || (currentTime - lastTouchTime < 1000)) {
    if (currentTime - lastBlinkTime > (blinkPattern * 100)) {
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState);
      lastBlinkTime = currentTime;
    }
  } 
  // Breathing effect when idle
  else {
    // Calculate breathing effect (sine wave pattern)
    float breath = (exp(sin(millis() / 2000.0 * PI)) - 0.36787944);
    int brightness = breath * 128;
    analogWrite(LED_BUILTIN, brightness);
  }
}

// Startup animation sequence
void startupAnimation() {
  // Play all notes
  for (int i = 0; i < 7; i++) {
    playTone(i);
    
    // Visual feedback
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  
  // Breathing effect demo
  for (int i = 0; i < 3; i++) {
    for (int b = 0; b < 256; b++) {
      analogWrite(LED_BUILTIN, b);
      delay(5);
    }
    for (int b = 255; b >= 0; b--) {
      analogWrite(LED_BUILTIN, b);
      delay(5);
    }
  }
  
  // Turn off LED
  digitalWrite(LED_BUILTIN, LOW);
}