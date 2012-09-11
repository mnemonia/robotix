extern "C"{
#include "sBoesewicht.h"
}

#include <Servo.h> 
#include <Ultrasonic.h>

long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

Ultrasonic ultrasonic(A5,A4);
const int ultrasonicClearThreshold = 0;
const int ultrasonicAttentionThreshold = 50;
const int ultrasonicDangerThreshold = 10;
int currentState = C6_CLEAR;

Servo wingLeftServo;
Servo wingRightServo;
const int wingBottomAngle = 70;
const int wingTopAngle = 130;
const int wingCenterAngle = 90;
 
int pos = 0;    // variable to store the servo position 
const int eyeLed = 13;
const int mouthLed = 12;
const int wingLed = 6;
const int speakerPin = 8;


void setup() 
{ 
  Serial.begin(9600);
  
  pinMode(eyeLed, OUTPUT);     
  pinMode(mouthLed, OUTPUT);
  pinMode(wingLed, OUTPUT);

  wingLeftServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  wingRightServo.attach(10);  // attaches the servo on pin 9 to the servo object 

  wingLeftServo.write(wingCenterAngle);  // attaches the servo on pin 9 to the servo object 
  wingRightServo.write(wingCenterAngle);  // attaches the servo on pin 9 to the servo object 
  
  if (fINIT_())
  {
  	IN_.InitChannel(C5_ON);
  }
  else 
  {
  	/* initialization failed, abort drive */
  }
  
} 
 
 
void loop() 
{ 
  
  detect();
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
   incrementTime();
  }  
} 

void incrementTime(){
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  
  while (TRG_.PENDING_.TIMEUP_){
    TRG_.TIMEUP_(); /* timeup call */
  }
}

void detect(){
  int detectedState = detectState();
  if(currentState == detectedState){
    return;
  }
  currentState = detectedState;
  IN_.ControllerChannel(detectedState);
}
  
int detectState(){
  int distance = ultrasonic.Ranging(CM);
  Serial.print("Distance is ");
  Serial.print(distance);
  Serial.print(" and results into state ");

  if(distance > ultrasonicClearThreshold){
    if(distance <= ultrasonicDangerThreshold){
      Serial.println("DANGER");
      return C6_DANGER;
    }else if(distance > ultrasonicDangerThreshold && distance <= ultrasonicAttentionThreshold){
      Serial.println("ATTENTION");
      return C6_ATTENTION;
    }
  }
  
  Serial.println("CLEAR");
  return C6_CLEAR;
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

void uCHAN_EyeOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_CLOSE:
                digitalWrite(eyeLed, LOW);
		break;
	case C3_OPEN:
                digitalWrite(eyeLed, HIGH);
		break;
	default: 
		break;
	}
}

void uCHAN_MouthOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_CLOSE:
                digitalWrite(mouthLed, LOW);
		/* user defined code */
		break;
	case C4_OPEN:
                digitalWrite(mouthLed, HIGH);
		break;
	default: 
		break;
	}
}

void uCHAN_WingLeftChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C1_BOTTOM:
                digitalWrite(wingLed, HIGH);
                wingLeftServo.write(wingTopAngle);                
		break;
	case C1_CENTER:
                digitalWrite(wingLed, LOW);
                wingLeftServo.write(wingCenterAngle);                
		break;
	case C1_TOP:
                digitalWrite(wingLed, HIGH);
                wingLeftServo.write(wingBottomAngle);                
		break;
	default: 
		break;
	}
}

void uCHAN_WingRightChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_BOTTOM:
                digitalWrite(wingLed, HIGH);
                wingRightServo.write(wingBottomAngle);                
		break;
	case C2_CENTER:
                digitalWrite(wingLed, LOW);
                wingRightServo.write(wingCenterAngle);                
		break;
	case C2_TOP:
                digitalWrite(wingLed, HIGH);
                wingRightServo.write(wingTopAngle);                
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

	OUT_.EyeOutChannel = uCHAN_EyeOutChannel;
	OUT_.MouthOutChannel = uCHAN_MouthOutChannel;
	OUT_.WingLeftChannel = uCHAN_WingLeftChannel;
	OUT_.WingRightChannel = uCHAN_WingRightChannel;
}  

} // extern "C"
