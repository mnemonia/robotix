#include "Receiver.h"

Receiver::Receiver(int pin){
  _pin = pin;
  pinMode(_pin, INPUT);
}

boolean Receiver::isOn(){
  return digitalRead(_pin) == HIGH;  
}
