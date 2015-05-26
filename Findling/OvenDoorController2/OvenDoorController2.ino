#include "Arduino.h"
#include "FindlingDoorController.h"

FindlingDoorController door_01 = FindlingDoorController(5, 7, 0, 255, 255, 0, 26, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("findl.ing light controller");
  door_01.shut();
}

void loop() {
  door_01.checkAndSetLight();
  door_01.update();
}
