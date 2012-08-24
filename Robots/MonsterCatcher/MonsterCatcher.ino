extern "C"{
#include "sMCUnit.h"
}

#include <Ultrasonic.h>
//#include <Servo.h> 
#include <SoftwareServo.h>


Ultrasonic ultrasonic(7,6);

////////////////////////////////////////
SoftwareServo servo;
//Servo servo;

int servoPin = 5;
int servoPos = 90;
int pos;
int slowStepRate = 1;
int fastStepRate = 10;
////////////////////////////////////////

long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

// motor A
int dir1PinA = 13;
int dir2PinA = 12;
int speedPinA = 10;
// motor B
// motor A
int dir1PinB = 11;
int dir2PinB = 8;
int speedPinB = 9;
unsigned long time;
int speed = 200;
int dir;


int bumperPin = 2;

void setup() {                
  Serial.begin(9600);
  
  initMotors();
  initBumper();  
  initServo();
  
  if (fINIT_())
  {
    IN_.WanderChannel(C4_START);
  }
  else 
  {
    /* initialization failed, abort drive */
  }  
}



void loop(){
  if(isBumpedIntoSomething()){
    Serial.println("BUMP");
    IN_.ObstacleDetection(C3_BUMP); 
  }else{
    if(isBedAbove()){
      IN_.BedDetectorChannel(C5_DETECT);
    }else{
      IN_.BedDetectorChannel(C5_NOT_DETECT);
    }
  } 
  

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
    incrementTime();
  }  
}

boolean isBumpedIntoSomething(){
  return digitalRead(bumperPin)==LOW;
}

boolean isBedAbove(){
  Serial.print("Bed is above: ");
  Serial.println(ultrasonic.Ranging(CM) < 30);
  return ultrasonic.Ranging(CM) < 30 ;
}

void incrementTime(){
  //  int sensorValue = analogRead(sensorPin);    

  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */

  while (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
  //  Serial.println("TICK");
}

void initMotors(){
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  
  time = millis();
  
  speed = 200;
  
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);

}

void initServo(){
  servo.attach(servoPin); 
  servo.setMaximumPulse(2000);
  //servo.write(servoPos);
  servo.write(90);                  
}

void initBumper(){
  pinMode(bumperPin, INPUT);
  digitalWrite(bumperPin,HIGH);
}

void servoGoDown(int steps){
  if((servoPos - steps) >= 10){
    servoPos -= steps;
  }
  
  servo.write(servoPos);
  delay(15);
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

void uCHAN_CatcherChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_BACK_TO_FRONT:
                servo.write(60); 
                Serial.println("BACK_TO_FRONT");               
		break;
	case C2_CENTER:
                servo.write(90);                
                Serial.println("CENTER");
		break;
	case C2_FRONT:
                servo.write(60);   
                Serial.println("FRONT");                               
		break;
	case C2_FRONT_TO_BACK:
                servo.write(100);  
                Serial.println("FRONT_TO_BACK");                               
		break;
	default: 
		break;
	}

        SoftwareServo::refresh();
        delay(15);
}

void uCHAN_DriveChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C1_BACKWARD:
              Serial.println("DRIVE BACKWARD");
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_BWD_LEFT:
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_BWD_RIGHT:
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_FORWARD:
              Serial.println("DRIVE FORWARD");

                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
                
		break;
	case C1_LEFT:
              Serial.println("DRIVE LEFT");
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_RIGHT:
              Serial.println("DRIVE RIGHT");
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_FWD_LEFT:
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_FWD_RIGHT:
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, LOW);
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

	OUT_.CatcherChannel = uCHAN_CatcherChannel;
	OUT_.DriveChannel = uCHAN_DriveChannel;
}

}
