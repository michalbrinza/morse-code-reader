
const int buttonPin = 2; // Connect button to pin 2 and GND

const int dashThreshold = 250;  // Longer than this is a dash, shorter is a dot
const int spaceThreshold = 1000; // Wait this long for a space between letters

unsigned long pressStartTime = 0;
unsigned long releaseTime = 0;
bool lastButtonState = HIGH; 
bool isPressed = false;
bool spacePrinted = true;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600);
  Serial.println("Ready:");
}

void loop() {
  // Read the button (LOW means pressed)
  bool currentButtonState = digitalRead(buttonPin);

  // 1. Button was just PRESED
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    pressStartTime = millis();
    isPressed = true;
    spacePrinted = false; // We are typing, so we don't need a space yet
    delay(50); // Debounce delay to stop button bounce
  }

  // 2. Button was just RELEASED
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    unsigned long pressDuration = millis() - pressStartTime;
    releaseTime = millis(); // Start timing the pause
    isPressed = false;

    // Check if it was a dot or a dash
    if (pressDuration > dashThreshold) {
      Serial.print("-"); // Dash
    } else if (pressDuration > 10) { // Ignore tiny accidental touches
      Serial.print("."); // Dot
    }
    delay(50); // Debounce delay
  }

  // 3. Button is NOT pressed (Check for spaces between letters)
  if (currentButtonState == HIGH && !isPressed && !spacePrinted) {
    if (millis() - releaseTime > spaceThreshold) {
      Serial.print(" "); // Print a space to separate letters
      spacePrinted = true;
    }
  }

  // Save the state for the next loop
  lastButtonState = currentButtonState;
}