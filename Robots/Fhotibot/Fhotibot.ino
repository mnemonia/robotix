extern "C"{
  #include "sTheUnit.h"
}

#include <AFMotor.h>
#include <Servo.h> 
#include <DistanceGP2Y0A21YK.h>

DistanceGP2Y0A21YK proxSensor;
int distance;
unsigned char distanceState;
 
//Servo traceServo;  // create servo object to control a servo 
//Servo headServo;  // create servo object to control a servo 

const int traceSensorLeftPin = A5; //analog pin 0
const int traceSensorRightPin = A4; //analog pin 0

//AF_DCMotor motorLeft(1/*, MOTOR12_64KHZ*/); // create motor #2, 64KHz pwm
//AF_DCMotor motorRight(2); // create motor #2, 64KHz pwm
const int motorSpeed = 250;

void setup(){
  Serial.begin(9600);
  pinMode(10, OUTPUT);      
  pinMode(11, OUTPUT);      
  pinMode(12, OUTPUT);      
  pinMode(13, OUTPUT);      
  
//  motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
//  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255
  proxSensor.begin(A5);
  distanceState = C3_;
  //traceServo.attach(9);
//  headServo.attach(10);

  if(!fINIT_()){
  // Fehler in fININT ...
  }

}

//
//C3_Clear
//

void loop(){
  distance = proxSensor.getDistanceCentimeter();

  if(distance>14){
    radar(C3_Clear);
  }else if(distance<=14 && distance>6){
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
/*

void rotateHead(){
  int val = analogRead(traceSensorLeftPin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  headServo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}
void rotateTrace(){
  int val = analogRead(traceSensorRightPin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  //traceServo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}

void forward(){
  motorLeft.run(FORWARD);      // turn it on going forward
  motorRight.run(FORWARD);      // turn it on going forward
}
void backward(){
  motorLeft.run(BACKWARD);      // turn it on going forward
  motorRight.run(BACKWARD);      // turn it on going forward
}
void turnShallowLeft(){
  motorLeft.run(RELEASE);      // turn it on going forward
  motorRight.run(FORWARD);      // turn it on going forward
}
void turnShallowRight(){
  motorLeft.run(FORWARD);      // turn it on going forward
  motorRight.run(RELEASE);      // turn it on going forward
}
void turnLeft(){
  motorLeft.run(BACKWARD);      // turn it on going forward
  motorRight.run(FORWARD);      // turn it on going forward
}
void turnRight(){
  motorLeft.run(FORWARD);      // turn it on going forward
  motorRight.run(BACKWARD);      // turn it on going forward
}
void stopNow(){
  motorLeft.run(RELEASE);      // turn it on going forward
  motorRight.run(RELEASE);      // turn it on going forward
}

void traceAnalog(){
  int val = analogRead(A0);
  Serial.print("A0 ");
  Serial.println(val);
  val = analogRead(A1);
  Serial.print("A1 ");
  Serial.println(val);
  val = analogRead(A2);
  Serial.print("A2 ");
  Serial.println(val);
  val = analogRead(A3);
  Serial.print("A3 ");
  Serial.println(val);
  val = analogRead(A4);
  Serial.print("A4 ");
  Serial.println(val);
  val = analogRead(A5);
  Serial.print("A5 ");
  Serial.println(val);
    Serial.println("-------");
}
*/
