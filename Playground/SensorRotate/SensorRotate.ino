#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
int maxDegree = 60;
int ledPin = 13;
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup(){
  Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 4 to the servo object 
  myservo.write(0);
  pinMode(ledPin, OUTPUT);
}
void hideEyePerson(){
  for(int pos = maxDegree; pos >= 0; pos -= 1)
  {                                  // in steps of 1 degree 
    digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
}
void showEyePerson(){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    for(int pos = 0; pos <= maxDegree; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
}
////////////////////////////
//LOOP
void loop(){
  sensorValue = analogRead(sensorPin);    
  Serial.println(sensorValue);
  showEyePerson();
  hideEyePerson(); 
  delay(500);
}
