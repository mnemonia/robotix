// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h> 
 
Servo servoHead;  // create servo object to control a servo 
Servo servoTracker;  // create servo object to control a servo 
const int servoHeadPin = 9;  // create servo object to control a servo 
const int servoTrackerPin = 10;  // create servo object to control a servo 

AF_DCMotor motor(1);
AF_DCMotor motor3(2);

const int proximityPin = A5;  // create servo object to control a servo 

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(200);
  motor3.setSpeed(200);
 
  motor.run(RELEASE);
  motor3.run(RELEASE);
  
  servoHead.attach(servoHeadPin,0,180);  // attaches the servo on pin 9 to the servo object 
  servoTracker.attach(servoTrackerPin,0,180);  // attaches the servo on pin 9 to the servo object 
  servoHead.write(0);
  servoTracker.write(0);

}

void loop() {
  uint8_t i;
  
  Serial.print("Prox: ");
  int val = analogRead(proximityPin);
  Serial.println(val);
  
  Serial.println("tick");
  
  motor.run(FORWARD);
  motor3.run(FORWARD);
  
  Serial.println("FWD");
  for(int i=0;i<90;i++){
    servoHead.write(i);                  // sets the servo position according to the scaled value 
    servoTracker.write(i);                  // sets the servo position according to the scaled value 
    delay(15);  
  }
  Serial.println("FWD done");
  delay(1000);
  
  Serial.println("BWD");
  for(int i=90;i>0;i--){
    servoHead.write(i);                  // sets the servo position according to the scaled value 
    servoTracker.write(i);                  // sets the servo position according to the scaled value 
    delay(15);  
  }
  Serial.println("BWD done");
  
//  motor.run(RELEASE);
  delay(1000);
/*
for (i=0; i<255; i++) {
    motor.setSpeed(i);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("tock");

  motor.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
    delay(10);
 }
  

  Serial.print("tech");
  motor.run(RELEASE);
  delay(1000);
  */
}
