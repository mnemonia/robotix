#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "FindlingDoorController.h"

FindlingDoorController door_01 = FindlingDoorController(5, 3, 0, 255, 255, 0, 26, 0);
FindlingDoorController door_02 = FindlingDoorController(8, 6, 0, 255, 255, 0, 26, 0);
FindlingDoorController door_03 = FindlingDoorController(11, 9, 0, 255, 255, 0, 26, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("findl.ing light controller");
  door_01.shut();
  door_02.shut();
  door_03.shut();  
}

void loop() {
  door_01.checkAndSetLight();
  door_02.checkAndSetLight();
  door_03.checkAndSetLight();
  door_01.update();
  door_02.update();
  door_03.update();
}
