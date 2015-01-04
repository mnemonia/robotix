extern "C"{
#include "sDriveUnit.h"
}

#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

int wanderLightCounter = 0;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long currentMillies = 0L;
long previousMillis = 0L;
long interval = 20;  

#define PROXIMITY_DANGER 350
#define PROXIMITY_ATTENTION 200
#define PROXIMITY_CLEAR 100

// motor A
int motorPinA1 = 13;
int motorPinA2 = 12;
int speedPinA = 10;
// motor B
// motor A
int motorPinB1 = 8;
int motorPinB2 = 11;
int speedPinB = 9;
unsigned long time;
int speed;
int dir;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize Lillebro...");
  pinMode(motorPinA1, OUTPUT);
  pinMode(motorPinA2, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(motorPinB1, OUTPUT);
  pinMode(motorPinB2, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  speed = 200;
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);

  pixels.begin(); // This initializes the NeoPixel library.
  
	/* Initializing CIP Machine */

  if (fINIT_())
  {
  	/* activation of drive loop */
        IN_.ProximityEvents(C4_CLEAR);
        //IN_.Events(C1_TRIGGER);
  }
  else 
  {
  	/* initialization failed, abort drive */
  }
  
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show(); // This sends the updated pixel color to the hardware.

  Serial.println("Initialize Lillebro DONE");
  
}
void checkAndSetProxomityLevel(){
  Serial.println("Checking proximity ...");
  switch(checkProximity()){
    case PROXIMITY_DANGER:
        Serial.println("Proximity is DANGER");
        pixels.setPixelColor(0, pixels.Color(0, 128, 0));
        pixels.show(); // This sends the updated pixel color to the hardware.
        IN_.ProximityEvents(C4_DANGER);
      break;
    case PROXIMITY_ATTENTION:
        Serial.println("Proximity is ATTENTION");
        pixels.setPixelColor(0, pixels.Color(255, 255, 0));
        pixels.show(); // This sends the updated pixel color to the hardware.
        IN_.ProximityEvents(C4_ATTENTION);
      break;
    case PROXIMITY_CLEAR:
    default: 
        Serial.println("Proximity is CLEAR");
        IN_.ProximityEvents(C4_CLEAR);
      break;
  }
}
void loop(){
  checkAndSetProxomityLevel();

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
    incrementTime();
  }  
}

int checkProximity(){
  int val = analogRead(A0);
  Serial.println(val);
  
  if(val < PROXIMITY_ATTENTION){
    return PROXIMITY_CLEAR;
  }
  if(val < PROXIMITY_DANGER){
    return PROXIMITY_ATTENTION;
  }
  return PROXIMITY_DANGER;
}

void incrementTime(){
  //  int sensorValue = analogRead(sensorPin);    


  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */

  while (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
  //  Serial.println("TICK");
}


void motorLeftFwd(){
  digitalWrite(motorPinA1, HIGH);
  digitalWrite(motorPinA2, LOW);
  Serial.println("motorLeftFwd");
}
void motorRightFwd(){
  digitalWrite(motorPinB1, HIGH);
  digitalWrite(motorPinB2, LOW);
  Serial.println("motorRightFwd");
}
void motorLeftBwd(){
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, HIGH);
  Serial.println("motorLeftBwd");
}
void motorRightBwd(){
  digitalWrite(motorPinB1, LOW);
  digitalWrite(motorPinB2, HIGH);
  Serial.println("motorRightBwd");
}
void motorRightStop(){
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, LOW);
  Serial.println("motorRightStop");
}
void motorLeftStop(){
  digitalWrite(motorPinB1, LOW);
  digitalWrite(motorPinB2, LOW);
  Serial.println("motorLeftStop");
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

/*
void loop2() {
  motorFwd();
  wait();
  motorStop();
  //wait();
  motorBwd();
  wait();
  motorStop();
  //wait();
  
  steeringLeft();
  wait();
  steeringNeutral();
  wait();
  steeringRight();  
  wait();
  steeringNeutral();

  wait();
  wait();
}
*/

extern "C" {

/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_LeftMotorActions (unsigned char name_)
{
  Serial.println("uCHAN_LeftMotorActions");
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_BWD:
                motorLeftBwd();
		break;
	case C2_FWD:
		motorLeftFwd();
		break;
	case C2_STOP:
                motorLeftStop();
		break;
	default: 
		break;
	}
}

void uCHAN_RightMotorActions (unsigned char name_)
{
  Serial.println("uCHAN_RightMotorActions");
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_BWD:
                motorRightBwd();
		break;
	case C3_FWD:
                motorRightFwd();
		break;
	case C3_STOP:
                motorRightStop();
		break;
	default: 
		break;
	}
}


void uCHAN_WanderLightActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_CHANGE:
Serial.println("uCHAN_WanderLightActions");
        wanderLightCounter++;
        if(wanderLightCounter > 255){
          wanderLightCounter = 0;
        }
        pixels.setPixelColor(0, pixels.Color(255 - wanderLightCounter, 0, wanderLightCounter));
        pixels.show(); // This sends the updated pixel color to the hardware.
                //pixels.setPixelColor(0, pixels.Color(255, 255, 0));
                //pixels.show(); // This sends the updated pixel color to the hardware.
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

	OUT_.LeftMotorActions = uCHAN_LeftMotorActions;
	OUT_.RightMotorActions = uCHAN_RightMotorActions;
	OUT_.WanderLightActions = uCHAN_WanderLightActions;
}

  
  
}// extern C
