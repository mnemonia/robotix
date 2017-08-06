#include "Ultrasound.h"
#include "Light.h"
#include "AdditionalLight.h"
#include "Button.h"

Ultrasound ultrasound(12,11);
Light rearLeft(6);
Light rearRight(9);

AdditionalLight led1(13);
AdditionalLight led2(10);

Button frontLeft(2);
Button frontRight(4);

void setup() {
  Serial.begin(9600); // Starts the serial communication
  rearLeft.on();
  rearRight.on();
  led2.on();
}

void loop() {
  if(frontLeft.isPushed()){
    led1.on();
  }else{
    led1.off();
  }  
  Serial.println(ultrasound.distance());
}
