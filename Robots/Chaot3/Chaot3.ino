extern "C"{
#include "sChaotUnit.h"
}
#include <Servo.h> 
 
Servo shakeServo;  // create servo object to control a servo 
const int shakeServoPin = 9;

#include <Stepper.h>

const int ZERO_TO_ONE_STEPS = 5;
const int stepsPerRevolution = 180;  // change this to fit the number of steps per revolution
                                     // for your motor
                                     
// initialize the stepper library on pins 8 through 11:
Stepper myStepper_1(stepsPerRevolution, 6, 7);            
Stepper myStepper_2(stepsPerRevolution, 2, 3);            

int stepCount = 0;         // number of steps the motor has taken

int photosensorPinLeft = A0;
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

void setup(){
  Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  shakeServo.attach(shakeServoPin);
  
  myStepper_1.setSpeed(200);
  myStepper_2.setSpeed(200);
  
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
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
   incrementTime();
  }  
}

void incrementTime(){
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  if (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
//  Serial.println("TICK");
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

void registerWriteAll(int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  for(int whichPin = 0; whichPin<8; whichPin++){
    bitWrite(bitsToSend, whichPin, whichState);
  }

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}

void rotateIndicatorFwdOnFirst(int steps){
   for(int i=0; i<steps; i++){
      myStepper_1.step(-stepsPerRevolution);
   }
}
void rotateIndicatorFwdOnSecond(int steps){
   for(int i=0; i<steps; i++){
      myStepper_2.step(stepsPerRevolution);
   }
}
void rotateIndicatorBwd(int steps){
   for(int i=0; i<steps; i++){
      myStepper_1.step(stepsPerRevolution);
   }
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
Serial.println("START");
              IN_.Start(C1_START);
		break;
	default: 
		break;
	}
}

void uCHAN_IndicatorActions (unsigned char name_, 
	union tDATA_IndicatorActions *data_)
{
  int number = data_->_Results.Number;
  Serial.print("IndicatorActions Number ");
  Serial.println(number);
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_INDICATE_HIGH:
                // rotateIndicatorFwd(number*ZERO_TO_ONE_STEPS);
		break;
	case C5_INDICATE_LOW:
                rotateIndicatorFwdOnFirst(number*ZERO_TO_ONE_STEPS);
		break;
	case C5_INDICATE_MEDIUM:
                rotateIndicatorFwdOnSecond(number*ZERO_TO_ONE_STEPS);
		break;
	case C5_RESET:
                stepCount = 0;
		break;
	default: 
		break;
	}
}

int theResultIndex;
int highestSensorData;
union tDATA_MeasureEvents data_MeasureEvents;

void uCHAN_MeasureActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_MEASURE:
Serial.println("MEASURE");
                registerWriteAll(LOW);
                theResultIndex = -1;
                highestSensorData = 0;
                
		for(int index = 0; index < 8; index++){
                  registerWrite(index, HIGH);
                  delay(50);
                }
                
		for(int index = 0; index < 8; index++){
                  registerWrite(index, HIGH);
                  delay(250);
                  int lastSensorData = analogRead(photosensorPinLeft);
                  delay(50);

                  if(lastSensorData > highestSensorData){
                    highestSensorData = lastSensorData;
                    theResultIndex = index;
                  } 
                }
                
                registerWrite(theResultIndex, HIGH);
                data_MeasureEvents._Results.Number = theResultIndex;
                IN_.MeasureEvents(C4_DONE, &data_MeasureEvents);
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
Serial.println("SHAKE CENTER");
		shakeServo.write(90);
		break;
	case C2_LEFT:
Serial.println("SHAKE LEFT");
		shakeServo.write(20);
		break;
	case C2_RIGHT:
Serial.println("SHAKE RIGHT");
		shakeServo.write(160);
		break;
	default: 
		break;
	}
}


void uCHAN_ChaoticActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C8_DETECT_HOLD:
Serial.println("DETECT HOLD");
registerWriteAll(HIGH);
		/* user defined code */
delay(6000);
IN_.ChaoticEvents(C7_HALTED);

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

	OUT_.ChaoticActions = uCHAN_ChaoticActions;
	OUT_.ControllerActions = uCHAN_ControllerActions;
	OUT_.IndicatorActions = uCHAN_IndicatorActions;
	OUT_.MeasureActions = uCHAN_MeasureActions;
	OUT_.ShakerActions = uCHAN_ShakerActions;
}

 }