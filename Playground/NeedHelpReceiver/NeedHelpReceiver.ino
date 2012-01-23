// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#undef int
#undef abs
#undef double
#undef float
#undef round

const int BUTTON_LED_PIN = 13;
const int BUTTON_PIN = 2;
int buttonState = 0;

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");
    
    pinMode(BUTTON_LED_PIN, OUTPUT);      
    pinMode(BUTTON_PIN, INPUT); 

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

        digitalWrite(BUTTON_LED_PIN, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
	    Serial.print((char)buf[i]);
	    Serial.print(" ");
	}
	Serial.println("");
    }
    
    buttonState = digitalRead(BUTTON_PIN);
    Serial.println(buttonState);
    if(buttonState==HIGH){
        digitalWrite(BUTTON_LED_PIN, LOW);    
    }
}
