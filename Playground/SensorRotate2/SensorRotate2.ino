// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
void setup() 
{ 
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  myservo.write(0);
  //delay(4000);                           // waits for the servo to get there 
  int theMax = 180;
  int theDeay = 20;
 // myservo.write(0);
  
  for(int i=0; i<theMax; i++){
    myservo.write(i);                  // sets the servo position according to the scaled value 
    delay(theDeay);                           // waits for the servo to get there 
  }
  for(int i=theMax; i>0; i--){
    myservo.write(i);                  // sets the servo position according to the scaled value 
    delay(theDeay);                           // waits for the servo to get there 
  }
  
} 
