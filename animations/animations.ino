#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define LED_PIN 6
#define PATTERN 1
// Delay in milliseconds
#define PAUSE 5000

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t off = matrix.Color(0 ,0, 0);


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.show();
  randomSeed(analogRead(0));
  Serial.begin(19200);
}

void loop() {
  switch(PATTERN){
    case 1: 
      play_house();  
  }
}

void play_house(){
  // step 1
  uint32_t colour = get_random_colour();
  turn_all_off();
  set_line(0, colour);
  set_line(7, colour);
  set_square(13, 19, colour);
  set_square(27, 37, colour);
  delay(PAUSE);
  // step 2
  colour = get_random_colour();
  turn_all_off();
  set_line(0, colour);
  set_line(7, colour);
  set_horizontal_line(0, colour);
  set_square(51, 61, colour);
  set_square(53, 59, colour);
  delay(PAUSE);
  // step 3
  colour = get_random_colour();
  turn_all_off();
  set_line(0, colour);
  set_line(7, colour);
  set_horizontal_line(0, colour);
  set_square(10, 22, colour);
  set_square(34, 46, colour);
  delay(PAUSE);
  
}

void set_square(int start, int finish, uint32_t colour){
  matrix.setPixelColor(start, colour);
  matrix.setPixelColor(start-1, colour);
  matrix.setPixelColor(finish-1, colour);
  matrix.setPixelColor(finish, colour);
  matrix.show();
}

void set_line(int start, uint32_t colour){
  int distance = 1+start*2; 
  int minimum = distance;
  int i = start;
  while (i < 64){
     matrix.setPixelColor(i, colour);
     if (distance == minimum){
        distance = 15-(start*2);
      }
      else{
        distance = 1+(start*2);  
      }
      i = i + distance; 
  }
  matrix.show();
}

void set_horizontal_line(int start, uint32_t colour){
  int i = start; 
  while (i < (start+8)){
    matrix.setPixelColor(i, colour);
    i++;
  }
  matrix.show();
}




void turn_all_off() {
  for (int i = 0; i < matrix.numPixels(); i++){
    matrix.setPixelColor(i, off); 
  } 
  matrix.show();  
}

uint32_t get_random_colour() {
  return matrix.Color(random(256), random(256), random(256));
}

