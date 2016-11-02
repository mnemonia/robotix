#include "Knob.h"
#include "Signal.h"

Knob knob(A7);
Signal theSignal(13);

void setup() {
  Serial.begin(9600);
  }

void loop() {
  if(knob.isDown()){
    theSignal.sendSignal(1500);
  }
  delay(25);
}
