extern "C"{
  #include "sTheUnit.h"
}

#include <AFMotor.h>
#include <Servo.h> 
#include <DistanceGP2Y0A21YK.h>

DistanceGP2Y0A21YK proxSensorLeft;
DistanceGP2Y0A21YK proxSensorRight;
int distance;
unsigned char distanceState;
 
//Servo traceServo;  // create servo object to control a servo 
//Servo headServo;  // create servo object to control a servo 

const int proxSensorLeftPin = A5; //analog pin 5
const int proxSensorRightPin = A4; //analog pin 4

AF_DCMotor motorLeft(1/*, MOTOR12_64KHZ*/); // create motor #2, 64KHz pwm
AF_DCMotor motorRight(2); // create motor #2, 64KHz pwm
const int motorSpeed = 200;

void setup(){
  Serial.begin(9600);

  motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255

  proxSensorLeft.begin(proxSensorLeftPin);
  proxSensorRight.begin(proxSensorRightPin);
  
  distanceState = C8_Clear;
//  traceServo.attach(9);
//  headServo.attach(10);

  if(!fINIT_()){
  // Fehler in fININT ...
  }

}

void loop(){
  distance = proxSensorLeft.getDistanceCentimeter();
  int distanceRight = proxSensorRight.getDistanceCentimeter();
  distance = distance > distanceRight ? distanceRight : distance;

  if(distance>19){
    radar(C8_Clear);
  }else if(distance<=19 && distance>9){
    radar(C8_Attention);
  }else{
    radar(C8_Danger);
  }
  delay(20);
}

void radar(unsigned char name_AutonomousDriveEvent){
  if(distanceState==name_AutonomousDriveEvent){
      return;
  }
  
  distanceState = name_AutonomousDriveEvent;
  Serial.println(name_AutonomousDriveEvent);
  
  //uCHAN_AutonomousDriveEvents(name_AutonomousDriveEvent);
    IN_.AutonomousDriveEvents(name_AutonomousDriveEvent);
  TRG_.CHAIN_();  
}

extern "C"
{

/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_AutonomousDriveEvents (unsigned char name_)
{
  IN_.AutonomousDriveEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_ObstacleEvents (unsigned char name_)
{
  IN_.ObstacleEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_RemoteControlEvents (unsigned char name_)
{
  IN_.RemoteControlEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_LeftMotor (unsigned char name_)
{
 	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_Backward:
          Serial.println("Left BACKWARD");
          motorLeft.run(BACKWARD);
  	  break;
	case C4_Forward:
          Serial.println("Left FORWARD");
          motorLeft.run(FORWARD);
          break;
	case C4_Stop:
          Serial.println("Left RELEASE");
          motorLeft.run(RELEASE);
          break;
	default: 
		break;
	}
}

void uCHAN_RightMotor (unsigned char name_)
{
  	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_Backward:
          Serial.println("Right BACKWARD");
          motorRight.run(BACKWARD);
          break;
	case C5_Forward:
          Serial.println("Right FORWARD");
          motorRight.run(FORWARD);
          break;
	case C5_Stop:
          Serial.println("Right RELEASE");
          motorRight.run(RELEASE);
          break;
	default: 
		break;
	}
}

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.AutonomousDriveEvents = uCHAN_AutonomousDriveEvents;
	OUT_.LeftMotor = uCHAN_LeftMotor;
	OUT_.ObstacleEvents = uCHAN_ObstacleEvents;
	OUT_.RemoteControlEvents = uCHAN_RemoteControlEvents;
	OUT_.RightMotor = uCHAN_RightMotor;
}

}

