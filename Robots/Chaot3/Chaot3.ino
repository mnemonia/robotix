extern "C"{
#include "sChaotUnit.h"
}
#include <Servo.h> 
 
Servo shakeServo;  // create servo object to control a servo 
const int shakeServoPin = 9;

#include <Stepper.h>


const int stepsPerRevolution = 2032;  // change this to fit the number of steps per revolution
                                     // for your motor
                                     
// initialize the stepper library on pins 8 through 11:
Stepper myStepper1(stepsPerRevolution, 7,6);            
Stepper myStepper2(stepsPerRevolution, 2,3);            
Stepper myStepper3(stepsPerRevolution, 5,4);            

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
  
  myStepper1.setSpeed(3);
  myStepper2.setSpeed(3);
  myStepper3.setSpeed(3);

  registerWriteAll(HIGH);
  //registerWriteAll(HIGH);
  
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


void rotateFwd1(int steps){
   for(int i=0; i<steps; i++){
      myStepper1.step(1);
   }
}
void rotateBwd1(int steps){
   for(int i=0; i<steps; i++){
      myStepper1.step(-1);
   }
}

void rotateFwd2(int steps){
   for(int i=0; i<steps; i++){
      myStepper2.step(1);
   }
}
void rotateBwd2(int steps){
   for(int i=0; i<steps; i++){
      myStepper2.step(-1);
   }
}

void rotateFwd3(int steps){
   for(int i=0; i<steps; i++){
      myStepper3.step(1);
   }
}
void rotateBwd3(int steps){
   for(int i=0; i<steps; i++){
      myStepper3.step(-1);
   }
}

void rotateIndicatorBwd(int steps){
   for(int i=0; i<steps; i++){
//      myStepper_1.step(stepsPerRevolution);
   }
}

extern "C" {
  const int IndicatorFigure0 =	0	;
const int IndicatorFigure1 =	254	;
const int IndicatorFigure2 =	508	;
const int IndicatorFigure3 =	762	;
const int IndicatorFigure4 =	1016	;
const int IndicatorFigure5 =	1270	;
const int IndicatorFigure6 =	1524	;
const int IndicatorFigure7 =	1778	;
const int IndicatorFigure8 =	2032	;

int IndicatorFigures[8] = {
  IndicatorFigure0,
  IndicatorFigure1,
  IndicatorFigure2,
  IndicatorFigure3,
  IndicatorFigure4,
  IndicatorFigure5,
  IndicatorFigure6,
  IndicatorFigure7
};

int currentMin = 0;
int currentMedium = 0;
int currentMax = 0;

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
          rotateFwd3(IndicatorFigures[number]);
          currentMax = number;
		break;
	case C5_INDICATE_LOW:
          rotateFwd1(IndicatorFigures[number]);
          currentMin = number;
		break;
	case C5_INDICATE_MEDIUM:
            rotateFwd2(IndicatorFigures[number]);
          currentMedium = number;            
		break;
	case C5_RESET:
          rotateBwd1(currentMin);
          rotateBwd2(currentMedium);
          rotateBwd3(currentMax);
                currentMin = 0;
                currentMedium = 0;
                currentMax = 0;
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
		shakeServo.write(105);
		break;
	case C2_LEFT:
Serial.println("SHAKE LEFT");
		shakeServo.write(20);
		break;
	case C2_RIGHT:
Serial.println("SHAKE RIGHT");
		shakeServo.write(180);
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
