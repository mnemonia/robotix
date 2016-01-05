#include "Knob.h"
#include "Arduino.h"

Knob::Knob(int pin){
    _pin = pin;
    pinMode(_pin, INPUT);
};

boolean Knob::isDown(){
  return digitalRead(_pin) == LOW;
};
