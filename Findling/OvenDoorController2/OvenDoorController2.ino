#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "FindlingNeoPixel.h"

FindlingNeoPixel p = FindlingNeoPixel(7, 0, 255, 255, 0, 26, 0);
//Adafruit_NeoPixel a = Adafruit_NeoPixel(1, 7, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("findl.ing light controller");
  p.turnOn();
  //a.begin();
  //a.setPixelColor(0, a.Color(0xFF, 0xCC, 0xFF));
  //a.show();
}

void loop() {
  //p.printState();
  p.update();
}
