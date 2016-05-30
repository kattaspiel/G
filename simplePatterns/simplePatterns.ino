#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define LED_PIN 6
#define BUTTON 2

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);
int buttonState = 0;
int count = 0;
uint32_t off = matrix.Color(0 ,0, 0);

void setup() {
  pinMode(BUTTON, INPUT);
  matrix.begin();
  matrix.show();
  randomSeed(analogRead(0));
}

void loop() {
  buttonState = digitalRead(BUTTON); 

  if(buttonState == HIGH){
    count = count + 1; 
    if (count == 12){
      // turn the matrix off
      count = 0;
      for (int i; i < matrix.numPixels(); i++){
          matrix.setPixelColor(i, off); 
      }
      matrix.show();
    }
  }
}
