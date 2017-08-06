#include "Arduino.h"
#include "Button.h"

Button::Button(int pin){
  pinMode(pin, INPUT);
  _pin = pin;
}

boolean Button::isPushed(){
  return digitalRead(_pin) == HIGH;
}
