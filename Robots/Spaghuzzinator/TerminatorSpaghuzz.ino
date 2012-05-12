#include <Servo.h> 
 
Servo yawServo;
Servo pitchServo;
int pos = 0;    // variable to store the servo position 
               
const int leftRed = 4;
const int leftYellow = 8;
const int rightRed = 7;
const int rightYellow = 6;
const int center = 5;


void out(int pin){
 pinMode(pin,OUTPUT);
}
void on(int pin){
  digitalWrite(pin,HIGH);
}
void off(int pin){
  digitalWrite(pin,LOW);
}

void setup() {                
  yawServo.attach(12);
  pitchServo.attach(11);
  
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  out(leftRed);     
  out(leftYellow);     
  out(rightRed);     
  out(rightYellow);     
  out(center);     

    on(center);

    yawServo.write(90);              // tell servo to go to position in variable 'pos' 
    pitchServo.write(90);              // tell servo to go to position in variable 'pos' 
}

void rotate() 
{ 
  int theDelay = 100;
  for(pos = 90; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    yawServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 120; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees
  {                                
    yawServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 90; pos < 100; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    pitchServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 100; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    pitchServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  }   
}

void loop() {
  
//  on(leftRed);
//  on(leftYellow);
//  on(rightRed);
//  on(rightYellow);

  on(leftRed);
  on(leftYellow);
  on(rightRed);
  on(rightYellow);
rotate();
  delay(1000);              // wait for a second
  on(leftRed);
  off(leftYellow);
  on(rightRed);
  off(rightYellow);
  delay(1000);              // wait for a second
  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);
  delay(1000);              // wait for a second
  on(leftRed);
  on(leftYellow);
  on(rightRed);
  on(rightYellow);
  delay(1000);              // wait for a second
  off(leftRed);
  off(leftYellow);
  off(rightRed);
  off(rightYellow);
  delay(1000);              // wait for a second
}
