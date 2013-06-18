//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#undef int
#undef abs
#undef double
#undef float
#undef round

const int upperCenterStatePin = 7;
int upperCenterState = LOW;

void setup()
{
  Serial.begin(9600);	  // Debugging only
  Serial.println("setup");

  pinMode(upperCenterStatePin, INPUT); 

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
}

void loop()
{
  int newUpperCenterState = digitalRead(upperCenterStatePin);
  Serial.println(upperCenterState);

  if(hasChanged(newUpperCenterState, upperCenterState)){
    upperCenterState = newUpperCenterState;
    if (upperCenterState == HIGH) {     
      transmit("UpperCenterOn");
    } 
    else {
      transmit("UpperCenterOff");
    }
  }

  delay(20);
}
void transmit(char *msg){
  digitalWrite(13, true); // Flash a light to show transmitting
  delay(150);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, false);
}

boolean hasChanged(int newState, int oldState){
  return newState != oldState;
}

