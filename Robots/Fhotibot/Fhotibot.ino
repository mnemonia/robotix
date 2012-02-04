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
  
  distanceState = C3_;
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
    radar(C3_Clear);
  }else if(distance<=19 && distance>9){
    radar(C3_Attention);
  }else{
    radar(C3_Danger);
  }
  delay(20);
}

void radar(unsigned char newDistanceState){
  if(distanceState==newDistanceState){
      return;
  }
  
  distanceState = newDistanceState;
  Serial.println(newDistanceState);
  IN_.Radar(newDistanceState);
  TRG_.CHAIN_();
}

extern "C"
{
void uCHAN__LeftDriver (unsigned char name_)
{
  switch (name_){
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

void uCHAN__RightDriver (unsigned char name_)
{
  switch (name_){
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
}

