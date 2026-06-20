
const int buttonPin = 2; 

const int dashThreshold = 250;  
const int spaceThreshold = 1000; 

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
  bool currentButtonState = digitalRead(buttonPin);


  if (currentButtonState == LOW && lastButtonState == HIGH) {
    pressStartTime = millis();
    isPressed = true;
    spacePrinted = false; 
    delay(50); 
  }


  if (currentButtonState == HIGH && lastButtonState == LOW) {
    unsigned long pressDuration = millis() - pressStartTime;
    releaseTime = millis();
    isPressed = false;

   
    if (pressDuration > dashThreshold) {
      Serial.print("-"); 
    } else if (pressDuration > 10) { 
      Serial.print("."); 
    }
    delay(50); 
  }

  if (currentButtonState == HIGH && !isPressed && !spacePrinted) {
    if (millis() - releaseTime > spaceThreshold) {
      Serial.print(" "); 
      spacePrinted = true;
    }
  }

  lastButtonState = currentButtonState;
}
