#include "LightController.h"
#include "LightSwitch.h"

LightController controller(A0,9);
LightSwitch lightSwitch(3);

void setup() {
    Serial.begin(9600);
    digitalWrite(9,HIGH);
    delay(250);
    digitalWrite(9,LOW);
}

void loop() {
  if(lightSwitch.isOn()){
    controller.tick();
  }else{
    controller.off();
  }
  delay(50);
}
