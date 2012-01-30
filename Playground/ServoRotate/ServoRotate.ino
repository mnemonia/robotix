#include <Servo.h> 

const int to = 180;

Servo traceServo;  // create servo object to control a servo 
Servo headServo;  // create servo object to control a servo 

void setup(){
  Serial.begin(9600);
  
  traceServo.attach(9);
  headServo.attach(10);

  toZero();
}

void servoShow(){
  
  toZero();
  delay(1000);
  toMin();
  delay(1000);
  toMax();
  delay(2000);
}

void loop(){
  headServo.write(45); 
  delay(1000);
  headServo.write(135); 
  delay(1000);
  //servoShow();
  
/*  rotateHead();
  rotateTrace();
  traceAnalog();
  delay(1000);
  */
}
void toZero(){  
  headServo.write(0);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}
void toMin(){
  for(int i=90; i>0; i--){
    headServo.write(i);                  // sets the servo position according to the scaled value 
    delay(20);                           // waits for the servo to get there 
  }
}
void toMax(){
  for(int i=to; i>90; i--){
    headServo.write(i);                  // sets the servo position according to the scaled value 
    delay(20);                           // waits for the servo to get there 
  }
}

