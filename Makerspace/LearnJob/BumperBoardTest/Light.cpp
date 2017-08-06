#include "Arduino.h"
#include "Light.h"

Light::Light(int pwmPin){
  pinMode(pwmPin,OUTPUT);
  _pwmPin = pwmPin;
}

void Light::on(){
    // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(_pwmPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
void Light::off(){
    // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(_pwmPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}


