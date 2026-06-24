#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>


#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


const int buttonPin = 2; 

const int dashThreshold = 250;  
const int spaceThreshold = 1000;   
const int wordThreshold = 3000;    
const int newLineThreshold = 2000; 

unsigned long pressStartTime = 0;
unsigned long releaseTime = 0;
bool lastButtonState = HIGH; 
bool isPressed = false;
bool spacePrinted = true;
bool wordPrinted = true;          
bool newLineTriggered = false; 

struct MorsePreklad {
  const char* morse;
  char pismeno;
};

MorsePreklad pismena[] = {
  {".-", 'A'},   {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},  {".", 'E'},
  {"..-.", 'F'}, {"--.", 'G'},   {"....", 'H'},  {"..", 'I'},   {".----", 'J'},
  {"-.-", 'K'},  {".-..", 'L'},  {"--", 'M'},    {"-.", 'N'},   {"---", 'O'},
  {".--.", 'P'}, {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},  {"-", 'T'},
  {"..-", 'U'},  {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'}, {"-.--", 'Y'},
  {"--..", 'Z'}
};

const int pocetPismen = sizeof(pismena) / sizeof(MorsePreklad);

String morseZnaky = ""; 
String aktualneSlovo = ""; 
char prelozNaPismeno(String morseKod) {
  for (int i = 0; i < pocetPismen; i++) {
    if (morseKod == pismena[i].morse) {
      return pismena[i].pismeno; 
    }
  }
  return '?'; 
}


void aktualizujDisplej() {
  tft.fillScreen(ST7735_BLACK); 
  tft.setCursor(10, 30);        
  tft.setTextSize(2);         
  tft.setTextColor(ST7735_WHITE);
  tft.println("SLOVO:");
  
  tft.setCursor(10, 60);
  tft.setTextSize(3);          
  tft.setTextColor(ST7735_GREEN);
  tft.println(aktualneSlovo);  
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600);
  

  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);
  
  aktualizujDisplej(); 
  Serial.println("System pripraveny.");
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // ČASŤ 1: Stlačenie tlačidla
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    pressStartTime = millis();
    isPressed = true;
    spacePrinted = false; 
    wordPrinted = false; 
    newLineTriggered = false; 
    delay(50); 
  }


  if (currentButtonState == LOW && isPressed && !newLineTriggered) {
    if (millis() - pressStartTime > newLineThreshold) {
      
      
      if (aktualneSlovo.length() > 0) {
        Serial.println(aktualneSlovo); 
      }
      
      aktualneSlovo = "";
      morseZnaky = "";
      
      aktualizujDisplej(); 
      
      newLineTriggered = true; 
    }
  }


  if (currentButtonState == HIGH && lastButtonState == LOW) {
    unsigned long pressDuration = millis() - pressStartTime;
    releaseTime = millis(); 
    isPressed = false;

    if (!newLineTriggered) {
      if (pressDuration > dashThreshold) {
        morseZnaky += "-"; 
      } else if (pressDuration > 10) { 
        morseZnaky += "."; 
      }
    }
    delay(50); 
  }


  if (currentButtonState == HIGH && !isPressed) {
    
  
    if (!spacePrinted && (millis() - releaseTime > spaceThreshold)) {
      if (morseZnaky.length() > 0) {
        char prelozene = prelozNaPismeno(morseZnaky);
        aktualneSlovo += prelozene; 
        
        aktualizujDisplej(); 
        morseZnaky = ""; 
      }
      spacePrinted = true;
    }

   
    if (!wordPrinted && (millis() - releaseTime > wordThreshold)) {
      if (aktualneSlovo.length() > 0) {
        Serial.println(aktualneSlovo); 
      }
      wordPrinted = true; 
    }
  }

  lastButtonState = currentButtonState;
}
