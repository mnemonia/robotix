#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "FindlingDoorController.h"

// FindlingDoorController door_01 = FindlingDoorController(9, 6, 255, 255, 10, 171, 10, 0);
 FindlingDoorController door_01 = FindlingDoorController(9, 6, 255, 255, 171, 255, 0, 255);

void setup() {
  door_01.shut();
//  Serial.begin(9600);
//  Serial.println("findl.ing light controller");
}

void loop() {
  door_01.checkAndSetLight();
  door_01.update();
}
