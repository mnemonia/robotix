#include "Signal.h"
#include "Arduino.h"

Signal::Signal(int pin){
  _pin = pin;  
  pinMode(_pin, OUTPUT);
}

void Signal::sendSignal(int millies){
  digitalWrite(_pin, HIGH);
  delay(millies);
  digitalWrite(_pin, LOW);
}
