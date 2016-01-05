#include "Receiver.h"
#include <Servo.h>
#include "Bell.h"

Receiver receiver(8);
Bell bell(6);

void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  if(receiver.isOn()){
    digitalWrite(13,HIGH);
    bell.ring();
  }else{
    digitalWrite(13,LOW);
  }
  delay(25);
}
