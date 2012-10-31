#include <Servo.h> 

Servo pinky;
Servo ring;
Servo middle;
Servo pointer;
Servo thumb;
Servo fingers[] = { 
  pinky,
  ring,
  middle,
  pointer,
  thumb
};

const int pinkyPin = 3;
const int ringPin = 5;
const int middlePin = 6;
const int pointerPin = 10;
const int thumbPin = 11; 

int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  pinky.attach(pinkyPin);
  ring.attach(ringPin);
  middle.attach(middlePin);
  pointer.attach(pointerPin);
  thumb.attach(thumbPin);
}  

void loop() 
{  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    for(int i = 0; i < 5; i++){
      fingers[i].write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);                       // waits 15ms for the servo to reach the position 
    }
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {  
    for(int i = 0; i < 5; i++){
      fingers[i].write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);                       // waits 15ms for the servo to reach the position 
    }      
  } 



} 

