#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "FindlingDoorController.h"

FindlingDoorController door_01 = FindlingDoorController(9, 6, 255, 255, 10, 171, 10, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("findl.ing light controller");
  door_01.shut();
}

void loop() {
  door_01.checkAndSetLight();
  door_01.update();
}
