#include <Servo.h>

Servo myservo;
int pos = 0;    // variable to store the servo position 


void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(11, OUTPUT);     
  pinMode(13, OUTPUT);     
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  digitalWrite(11, HIGH);   // set the LED on  
}

void loop() {
  digitalWrite(13, HIGH);   // set the LED on
  for(pos = 5; pos < 175; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  delay(1000);          
  digitalWrite(13, LOW);
  delay(1000);          
  digitalWrite(13, HIGH);
  for(pos = 175; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  digitalWrite(13, LOW);
  delay(1000);
}
