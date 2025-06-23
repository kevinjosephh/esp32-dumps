#define TOUCH_PIN T0   // Touch sensor GPIO4 (T0)
#define LED_PIN 2      // Built-in LED

// Duration thresholds (in milliseconds)
#define DOT_DASH_THRESHOLD 300   // Midpoint between dot and dash
#define LETTER_GAP 400           // Time between symbols ending a letter
#define WORD_GAP 1200            // Time between letters forming different words
#define DEBOUNCE_TIME 50         // Minimum valid press

// Morse code lookup table for A-Z and 0-9
const char* morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",  // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",    // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                           // U-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

String currentSequence = "";
unsigned long lastRelease = 0;
bool decoding = false;
bool touchActive = false;
unsigned long lastTouchTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("\n📡 Improved Morse Code Receiver Ready");
  Serial.println("👉 Tap GPIO4 pin: short = DOT (.), long = DASH (-)");
  Serial.println("-------------------------------------------------");
}

void loop() {
  int touchValue = readAveragedTouch();  // Smoothed sensor value

  // Touch started
  if (!touchActive && touchValue < 25) {
    touchActive = true;
    digitalWrite(LED_PIN, HIGH);
    lastTouchTime = millis();
  }

  // Touch ended
  if (touchActive && touchValue > 30) {
    touchActive = false;
    digitalWrite(LED_PIN, LOW);

    long duration = millis() - lastTouchTime;

    if (duration > DEBOUNCE_TIME) {
      if (duration < DOT_DASH_THRESHOLD) {
        Serial.print(".");
        currentSequence += ".";
      } else {
        Serial.print("-");
        currentSequence += "-";
      }

      lastRelease = millis();
      decoding = true;
    }
  }

  if (!touchActive && decoding && millis() - lastRelease > LETTER_GAP) {
    decodeSequence();
    decoding = false;
  }

  // Add space between words if no input for long time
  if (currentSequence.isEmpty() && millis() - lastRelease > WORD_GAP) {
    Serial.print(" ");
    lastRelease = millis();  // Prevent repeat spaces
  }
}

// Smooth touch reading by averaging multiple samples
int readAveragedTouch() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += touchRead(TOUCH_PIN);
    delay(2);
  }
  return sum / 5;
}

// Decode the Morse sequence into alphanumeric character
void decodeSequence() {
  if (currentSequence.length() == 0) return;

  int tableSize = sizeof(morseTable) / sizeof(morseTable[0]);
  bool found = false;

  for (int i = 0; i < tableSize; i++) {
    if (currentSequence == morseTable[i]) {
      Serial.print(" -> ");
      if (i < 26)
        Serial.println(char('A' + i));
      else
        Serial.println(char('0' + (i - 26)));
      found = true;
      break;
    }
  }

  if (!found) {
    Serial.print(" -> [Invalid: ");
    Serial.print(currentSequence);
    Serial.println("]");
  }

  currentSequence = "";
}
