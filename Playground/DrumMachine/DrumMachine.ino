// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

#define MAX_SNAIR 70
#define MAX_SNAIR_RETURN 110
#define MAX_BASE 10
#define MAX_BASE_RETURN 30
#define SERVO_DELAY 10

Servo snairDrum;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo baseDrum;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  snairDrum.attach(9);  // attaches the servo on pin 9 to the servo object 
  baseDrum.attach(6);
/*
  for(pos = 0; pos <= MAX_SNAIR; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    snairDrum.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(SERVO_DELAY);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 0; pos <= MAX_BASE; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    baseDrum.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(SERVO_DELAY);                       // waits 15ms for the servo to reach the position 
  } 
  */
} 
 
void hit(){
  int endPos = MAX_SNAIR;
  snairDrum.write(endPos);
  for(pos = endPos; pos < MAX_SNAIR_RETURN; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    snairDrum.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(SERVO_DELAY);                       // waits 15ms for the servo to reach the position 
  } 
}
void hitBase(){
  int endPos = MAX_BASE;
  baseDrum.write(endPos);
  for(pos = endPos; pos < MAX_BASE_RETURN; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    baseDrum.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(SERVO_DELAY);                       // waits 15ms for the servo to reach the position 
  } 
}
void hitShadowNote(){
  int endPos = 80;
  snairDrum.write(endPos);
  for(pos = endPos; pos < 100; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    snairDrum.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}
void wait4(){
  delay(400);
}
void wait1(){
  delay(100);
}
void wait50(){
  delay(50);
}
void groove(){
  for(int i = 0; i<3; i++){
    hit();
    hitShadowNote();
    hitShadowNote();
    wait1();
    hitBase();
    wait1();
  }
  for(int i = 0; i<3; i++){
    hitShadowNote();
    wait1();
  }
    hitBase();
    wait1();
}
void groove33(){
  for(int i = 0; i<3; i++){
    hit();
    hitShadowNote();
    hitBase();
    wait1();
  }
  for(int i = 0; i<2; i++){
    hitShadowNote();
    wait1();
  }
    hitBase();
    wait1();
}

void loop() 
{ 
  groove33();
  //groove();

} 
