extern "C"{
#include "sTheUnit.h"
}
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#undef int
#undef abs
#undef double
#undef float
#undef round
void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");
  pinMode(13, OUTPUT); 
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  if(!fINIT_()){
    // Fehler in fININT ...
  }
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    //digitalWrite(13, true); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");

    char str1[buflen+1];
    for (i = 0; i < buflen; i++)
    {
      Serial.print((char)buf[i]);
      Serial.print(" ");
      str1[i] = (char)buf[i];
    }
    str1[buflen] = '\0';

    Serial.println("");
    Serial.println(str1);

    if(strcmp(str1, "UpperCenterOn") == 0){
      Serial.println("C1_UPPER_CENTER_ON");
      IN_.CommandChannel(C1_UPPER_CENTER_ON);
    }
    else if(strcmp(str1, "UpperCenterOff\0") == 0){
      Serial.println("C1_UPPER_CENTER_OFF");
      IN_.CommandChannel(C1_UPPER_CENTER_OFF);
    }

    //digitalWrite(13, false);
  }
}


extern "C" {

  /*********************************************************************
   * 	User defined Output Channel Functions
   *********************************************************************/

  /* Output Channel Functions,
   	called by CIP Machine when a Message is written.
   	User defined function, with name to consider as suggestion */

  /* Parameters
   	name_		name value of message */

  void uCHAN_UpperCenterLightChan (unsigned char name_)
  {
    /* Accessing MESSAGE */
    switch (name_)
    {
    case C2_OFF:
      digitalWrite(13,LOW);
      break;
    case C2_ON:
      digitalWrite(13,HIGH);
      break;
    default: 
      break;
    }
  }


  /*********************************************************************
   * 	User defined Output Channel Interface Initialization Function
   *********************************************************************/

  void iCHAN_(void)
  {
    /* Initializing Input Error Function only if Input Error Option set */

#ifdef _EINPUT__
    IN_.EINPUT_ = uEINPUT_;
#endif 

    /* Initializing Output Interface */

    OUT_.UpperCenterLightChan = uCHAN_UpperCenterLightChan;
  }

}// extern "C"



