#include "Arduino.h"
#include "AdditionalLight.h"

AdditionalLight::AdditionalLight(int pin){
  pinMode(pin,OUTPUT);
  _pin = pin;
}

void AdditionalLight::on(){
  digitalWrite(_pin, HIGH);
}
void AdditionalLight::off(){
  digitalWrite(_pin, LOW);
}


