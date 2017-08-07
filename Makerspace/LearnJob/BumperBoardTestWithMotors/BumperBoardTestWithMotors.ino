#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "Ultrasound.h"
#include "Light.h"
#include "AdditionalLight.h"
#include "Button.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motorRight = AFMS.getMotor(1);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(2);

Ultrasound ultrasound(12,11);
Light rearLeft(6);
Light rearRight(9);

AdditionalLight led1(13);
AdditionalLight led2(10);

Button frontLeft(2);
Button frontRight(4);

void setup() {
  Serial.begin(9600); // Starts the serial communication
  AFMS.begin();  // create with the default frequency 1.6KHz
  rearLeft.on();
  rearRight.on();
  led2.on();

  motorRight->setSpeed(150);
  motorLeft->setSpeed(150);
  motorRight->run(FORWARD);
  motorLeft->run(FORWARD);
  // turn on motor
  motorRight->run(RELEASE);
  motorLeft->run(RELEASE);
}

void loop() {
  if(frontLeft.isPushed()){
    led1.on();
  }else{
    led1.off();
  }  
  Serial.println(ultrasound.distance());
}
