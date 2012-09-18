extern "C"{
#include "sBoesewicht.h"
}

#include <MsTimer2.h>
#include <Servo.h> 
#include <Ultrasonic.h>

const int timerInMillies = 60;

//const int countSinusSquareLookupTableEntries = 62;
//const int sinusSquareLookupTable[] = {70, 70, 70, 70, 70, 71, 71, 72, 72, 73, 74, 75, 76, 77, 79, 80, 81, 83, 84, 85, 86, 87, 88, 88, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 92, 92, 93, 94, 95, 96, 97, 99, 100, 101, 103, 104, 105, 106, 107, 108, 108, 109, 109, 110, 110, 110, 110, 110, 110};
const int countSinusSquareLookupTableEntries = 368;
const int sinusSquareLookupTable[] = {67, 67, 67, 69, 69, 67, 69, 69, 69, 69, 67, 67, 67, 65, 65, 65, 65, 65, 65, 65, 65, 63, 65, 65, 67, 69, 69, 65, 65, 65, 65, 65, 65, 61, 59, 59, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 56, 54, 54, 52, 52, 52, 54, 50, 50, 46, 46, 46, 44, 44, 42, 40, 40, 38, 57, 65, 57, 37, 35, 35, 33, 33, 31, 31, 31, 31, 31, 33, 33, 33, 35, 35, 35, 35, 37, 37, 40, 42, 42, 44, 46, 50, 56, 56, 54, 57, 57, 59, 65, 67, 69, 67, 73, 73, 73, 80, 82, 78, 80, 80, 82, 82, 84, 88, 92, 92, 92, 92, 90, 88, 82, 80, 76, 75, 75, 69, 69, 67, 63, 61, 59, 59, 57, 57, 52, 57, 42, 40, 38, 35, 35, 33, 37, 31, 31, 31, 31, 33, 38, 33, 33, 35, 38, 38, 42, 46, 52, 54, 57, 59, 67, 69, 69, 71, 78, 78, 80, 82, 86, 88, 90, 92, 90, 90, 90, 84, 78, 75, 69, 69, 67, 69, 54, 48, 71, 57, 38, 33, 31, 31, 31, 31, 31, 31, 29, 29, 31, 31, 33, 35, 38, 57, 42, 46, 50, 56, 57, 59, 65, 69, 69, 75, 80, 80, 84, 92, 92, 95, 97, 97, 99, 99, 103, 92, 95, 88, 95, 80, 78, 69, 69, 63, 61, 56, 90, 57, 69, 40, 57, 40, 38, 35, 33, 33, 31, 31, 33, 33, 35, 37, 35, 57, 37, 42, 38, 38, 42, 44, 50, 52, 54, 57, 57, 59, 63, 82, 67, 69, 75, 80, 80, 80, 82, 86, 90, 95, 97, 99, 97, 103, 105, 105, 111, 114, 120, 120, 116, 118, 118, 118, 118, 118, 118, 118, 116, 118, 118, 118, 118, 116, 118, 116, 118, 118, 118, 118, 118, 118, 118, 118, 118, 120, 112, 109, 107, 101, 99, 92, 88, 82, 78, 75, 69, 114, 69, 59, 57, 57, 50, 42, 40, 38, 35, 38, 31, 29, 29, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 31, 29, 29, 31, 29, 33, 33, 35, 37, 40, 46, 57, 59, 61, 63, 67, 69, 73};
int currentValueIndex = countSinusSquareLookupTableEntries / 2;


long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

Ultrasonic ultrasonic(A5,A4);
const int ultrasonicClearThreshold = 0;
const int ultrasonicAttentionThreshold = 60;
const int ultrasonicDangerThreshold = 50;
int currentState = C6_CLEAR;

Servo wingLeftServo;
Servo wingRightServo;
const int wingBottomAngle = 70;
const int wingTopAngle = 130;
//const int wingCenterAngle = 90;
const int wingCenterAngle = 100;
const int wingInitialAngle = wingCenterAngle;
 
int pos = 0;    // variable to store the servo position 
const int eyeLed = 13;
const int mouthLed = 12;
const int wingLed = 6;
const int speakerPin = 8;
const int movmentIndicatorPin = 4;
const int wingLeftServoPin = 9;
const int wingRightServoPin = 10;

/*
* This is the function that gets called periodically.
*/
void moveUp()
{
  doMove();
  incrementOrStop();
}

void moveDown()
{
  doMove();
  decrementOrStop();
}

void doMove(){
  moveServoTo(angle());
  Serial.print("Moving to ");
  Serial.println(angle());
  
  indicateMovement();
}

void moveServoTo(int angle){
  Serial.println(angle);
  wingLeftServo.write(angle); 
}

int angle(){
  return sinusSquareLookupTable[currentValueIndex];
}

void indicateMovement()
{
  static boolean output = HIGH;
  
  digitalWrite(movmentIndicatorPin, output);
  output = !output;
}

void incrementOrStop(){
  currentValueIndex++;
  if(currentValueIndex == countSinusSquareLookupTableEntries - 1){
    stopMove();
  }
}

void decrementOrStop(){
  currentValueIndex--;
  if(currentValueIndex == 0){
    stopMove();
  }
}

void stopMove(){
  MsTimer2::stop();
//  wingLeftServo.detach();
  IN_.WingControllerInC(C8_ReachedAxisEnd);
}

void setupMovementIndicator(){
  pinMode(movmentIndicatorPin, OUTPUT);
}

void setupTimer2(){
  MsTimer2::start();
}

void setupServo(){  
  wingLeftServo.attach(wingLeftServoPin);  // attaches the servo on pin 9 to the servo object 
  wingRightServo.attach(wingRightServoPin);  // attaches the servo on pin 9 to the servo object 
  wingLeftServo.write(wingCenterAngle);  // attaches the servo on pin 9 to the servo object 
  wingRightServo.write(wingCenterAngle);  // attaches the servo on pin 9 to the servo object 
}

void setup(){
  Serial.begin(9600);

  setupMovementIndicator();
  setupServo();  
  
  pinMode(eyeLed, OUTPUT);     
  pinMode(mouthLed, OUTPUT);
  pinMode(wingLed, OUTPUT);

  tone(speakerPin,440/2,1000 / 4);  
  delay(1000);
  noTone(speakerPin);
  
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
  
  Serial.println("TICK");
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

void uCHAN_WingControllerOutC (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C7_Move:
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
                Serial.println("WLCBOTTOM");
//                //MsTimer2::stop();
//                MsTimer2::set(timerInMillies, moveDown);
//                MsTimer2::start();
                
  wingLeftServo.attach(wingLeftServoPin);  // attaches the servo on pin 9 to the servo object 
                wingLeftServo.write(wingTopAngle);                
                delay(1000);
                wingLeftServo.detach();                
  IN_.WingControllerInC(C8_ReachedAxisEnd);                
		break;
	case C1_CENTER:
                digitalWrite(wingLed, LOW);
                Serial.println("WLCCENTER");
  wingLeftServo.attach(wingLeftServoPin);  // attaches the servo on pin 9 to the servo object 
                wingLeftServo.write(wingCenterAngle);         
                delay(1000);
                wingLeftServo.detach();                
  IN_.WingControllerInC(C8_ReachedAxisEnd);
  		break;
	case C1_TOP:
                digitalWrite(wingLed, HIGH);
                Serial.println("WLCTOP");

                //MsTimer2::stop();
//                MsTimer2::set(timerInMillies, moveUp);
//                MsTimer2::start();

  wingLeftServo.attach(wingLeftServoPin);  // attaches the servo on pin 9 to the servo object 
                  wingLeftServo.write(wingBottomAngle);                
                delay(1000);
                wingLeftServo.detach();                
  IN_.WingControllerInC(C8_ReachedAxisEnd);
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
	OUT_.WingControllerOutC = uCHAN_WingControllerOutC;
	OUT_.WingLeftChannel = uCHAN_WingLeftChannel;
	OUT_.WingRightChannel = uCHAN_WingRightChannel;
}  

} // extern "C"
