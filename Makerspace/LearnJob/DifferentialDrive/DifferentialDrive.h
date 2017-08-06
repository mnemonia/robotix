#ifndef DifferentialDrive_h
#define DifferentialDrive_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class DifferentialDrive
{
  public:
    DifferentialDrive(int leftMotorPort, int rightMotorPort);
    void setup();
    
    void forward();
    void backward();
    void stop();
    
  private:
    int _leftMotorPort;
    int _rightMotorPort;
    Adafruit_MotorShield _adafruitMotorShield;
    Adafruit_DCMotor *_motorLeft;
    Adafruit_DCMotor *_motorRight;
    int mapPercentageToPwm(float value);

};
#endif

