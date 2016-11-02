#include "Knob.h"
#include "Arduino.h"

Knob::Knob(int pin){
    _pin = pin;
    pinMode(_pin, INPUT);
};

boolean Knob::isDown(){
  Serial.println(digitalRead(A7));
  return digitalRead(A7) == LOW;
};
