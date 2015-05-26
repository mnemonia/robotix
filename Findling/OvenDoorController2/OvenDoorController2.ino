#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "FindlingDoorController.h"
//#include "FindlingMagnetDoorLock.h"

//FindlingNeoPixel light_01 = FindlingNeoPixel(7, 0, 255, 255, 0, 26, 0);
//FindlingMagnetDoorLock door_01 = FindlingMagnetDoorLock(5);
FindlingDoorController door_01 = FindlingDoorController(5, 7, 0, 255, 255, 0, 26, 0);
//Adafruit_NeoPixel a = Adafruit_NeoPixel(1, 7, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("findl.ing light controller");
  //light_01.turnOn();
  door_01.shut();
  //a.begin();
  //a.setPixelColor(0, a.Color(0xFF, 0xCC, 0xFF));
  //a.show();
}

void loop() {
  door_01.checkAndSetLight();
  door_01.update();
}
