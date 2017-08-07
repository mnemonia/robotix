#include "Arduino.h"
#include "Ultrasound.h"

Ultrasound::Ultrasound(int echoPin, int triggerPin)
{
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  _echoPin = echoPin;
  _triggerPin = triggerPin;
}
int Ultrasound::distance(){
   // Clears the trigPin
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(_echoPin, HIGH);
  // Calculating the distance
  int distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);  
  return distance;
}

