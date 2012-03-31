extern "C"{
#include "sChaotUnit.h"
}
#include <Servo.h> 
 
Servo shakeServo;  // create servo object to control a servo 
const int shakeServoPin = 8;

int photosensorPinLeft = A0;
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

long lastTickInMillies = 0L;
long currentMillies = 0L;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  shakeServo.attach(shakeServoPin);
  
  if (fINIT_())
  {
    IN_.Start(C1_START);
  }
  else 
  {
    /* initialization failed, abort drive */
  }
}

void loop(){
  currentMillies = millis();
  if(lastTickInMillies + 1000 > currentMillies){
    lastTickInMillies = currentMillies;
    incrementTime();
  }
  delay(10);
}

void incrementTime(){
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  if (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
  Serial.println("TICK");
}

// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}

extern "C" {

  /*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_ControllerActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C6_DRAWED:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_IndicatorActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_INDICATE_HIGH:
		/* user defined code */
		break;
	case C5_INDICATE_LOW:
		/* user defined code */
		break;
	case C5_INDICATE_MEDIUM:
		/* user defined code */
		break;
	case C5_RESET:
		/* user defined code */
		break;
	default: 
		break;
	}
}

int theResultIndex;
int lowestSensorData;

void uCHAN_MeasureActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_MEASURE:
                theResultIndex = -1;
                lowestSensorData = 10000;
		for(int index = 0; index < 8; index++){
                  registerWrite(index, HIGH);
                  int lastSensorData = analogRead(photosensorPinLeft);
                  
                  if(lastSensorData < lowestSensorData){
                    lowestSensorData = lastSensorData;
                    theResultIndex = index;
                  } 
                }
                
                registerWrite(theResultIndex, HIGH);
                IN_.MeasureEvents(C4_DONE);
		break;
	default: 
		break;
	}
}

void uCHAN_ShakerActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_CENTER:
		shakeServo.write(90);
		break;
	case C2_LEFT:
		shakeServo.write(0);
		break;
	case C2_RIGHT:
		shakeServo.write(180);
		break;
	default: 
		break;
	}
}


/*********************************************************************
	User defined Output Channel Interface Initialization Function
*********************************************************************/

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.ControllerActions = uCHAN_ControllerActions;
	OUT_.IndicatorActions = uCHAN_IndicatorActions;
	OUT_.MeasureActions = uCHAN_MeasureActions;
	OUT_.ShakerActions = uCHAN_ShakerActions;
}

  
}
