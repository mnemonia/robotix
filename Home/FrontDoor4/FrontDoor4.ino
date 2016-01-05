#include "Knob.h"
#include "Signal.h"

Knob knob(8);
Signal theSignal(2);

void setup() {;}

void loop() {
  if(knob.isDown()){
    theSignal.sendSignal(500);
  }
  delay(25);
}
