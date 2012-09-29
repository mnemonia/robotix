// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Ultrasonic.h>
#include <Servo.h> 
 
Ultrasonic ultrasonic(A5,A4);
const int ultrasonicClearThreshold = 68;
const int ultrasonicSomethingThereThreshold = 64;
const int ultrasonicAttentionThreshold = 55;
const int ultrasonicDangerThreshold = 40;

Servo leftServo;  // create servo object to control a servo 
Servo rightServo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int distance;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  leftServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  rightServo.attach(10);  // attaches the servo on pin 9 to the servo object 
  randomSeed(analogRead(A0));
  digitalWrite(7,LOW);
  
} 
 
void loop() 
{ 
  distance = ultrasonic.Ranging(CM);
//  Serial.println(val);
  if(!isClear(distance)){
    leftServo.write(withLeftMove(distance));                  // sets the servo position according to the scaled value 
    delay(10);                           // waits for the servo to get there 
    rightServo.write(withRightMove(distance));                  // sets the servo position according to the scaled value 
    delay(10);                           // waits for the servo to get there 
  }else{
  
  }

  if(isAttention(distance)){
    digitalWrite(6,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  }else if(isDanger(distance)){
    digitalWrite(6,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
  }else if(isSomethingThere(distance)){
    digitalWrite(6,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(6,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }
  

  if(isAttention(distance)){
    digitalWrite(7,HIGH);
  }else if(isDanger(distance)){
    digitalWrite(7,HIGH);
  }else if(isSomethingThere(distance)){
    digitalWrite(7,LOW);
  }else{
    digitalWrite(7,LOW);
  }
  
  
 // delay(30);                           // waits for the servo to get there 
}

int angle(int value){
  return map(value, 30, 88, 60, 130);     // scale it to use it with the servo (value between 0 and 180) 
}
int withLeftMove(int value){
/*  if(isDanger(value)){
    return getRight(angle(value));
  }
  */
  return getLeft(angle(value));
}

int withRightMove(int value){
  if(isDanger(value)){
    return getRight(angle(value));
  }
  return getLeft(angle(value));
}
boolean isClear(int value){
  return value == 0 || value >= ultrasonicClearThreshold;
}
boolean isDanger(int value){
  return value > 0 && value <= ultrasonicDangerThreshold;
}
boolean isAttention(int value){
  return value > ultrasonicDangerThreshold && value <= ultrasonicAttentionThreshold;
}
boolean isSomethingThere(int value){
  return value > ultrasonicAttentionThreshold && value <= ultrasonicSomethingThereThreshold;
}
int getLeft(int value){
  return value;
}
int getRight(int value){
  return 180 - getLeft(value);
}
