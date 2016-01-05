#include "Bell.h"

Bell::Bell(int pin){
  _pin = pin;
  //pinMode(_pin, OUTPUT);  
  _pos = 0;
}

void Bell::ring(){
  myservo.attach(_pin);  // attaches the servo on pin 9 to the servo object 
  left();
  right();
  left();
  right();
  left();
  right();
  left();
  right();
  myservo.detach();
}

void Bell::left(){
  for(_pos = 0; _pos <= 120; _pos += 5) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(_pos);              // tell servo to go to _position in variable '_pos' 
    delay(15);                       // waits 15ms for the servo to reach the _position 
  } 
}
void Bell::right(){
  for(_pos = 120; _pos>=0; _pos-=5)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(_pos);              // tell servo to go to _position in variable '_pos' 
    delay(15);                       // waits 15ms for the servo to reach the _position 
  } 
}

