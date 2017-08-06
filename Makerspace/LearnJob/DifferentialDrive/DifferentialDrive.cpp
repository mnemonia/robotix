#include "Arduino.h"
#include "DifferentialDrive.h"
/**
 * The Differential-Drive is the logical implementation of the physical
 * differential drive. This source-code is used in the 
 * Makerspace of the Kantonsschule Glarus to learn about mobile robots.
 * @author: nils@birkeland.ch
 */
DifferentialDrive::DifferentialDrive(int leftMotorPort, int rightMotorPort)
{
  _leftMotorPort = leftMotorPort;
  _rightMotorPort = rightMotorPort;
  _adafruitMotorShield = Adafruit_MotorShield(); 
}

void DifferentialDrive::setup()
{
  _motorLeft = _adafruitMotorShield.getMotor(_leftMotorPort);
  _motorRight = _adafruitMotorShield.getMotor(_rightMotorPort);
  _adafruitMotorShield.begin();  
}

void DifferentialDrive::forward()
{
  int speedInPercentage = 0.5; // That is 50% speed
  int speedInPwmScale = mapPercentageToPwm(speedInPercentage);
  _motorLeft->setSpeed(speedInPwmScale);
  _motorRight->setSpeed(speedInPwmScale);
  _motorLeft->run(FORWARD);
  _motorRight->run(FORWARD);
}

void DifferentialDrive::backward()
{
  int speedInPercentage = 0.3; // That is 30% speed
  int speedInPwmScale = mapPercentageToPwm(speedInPercentage);
  _motorLeft->setSpeed(speedInPwmScale);
  _motorRight->setSpeed(speedInPwmScale);
  _motorLeft->run(BACKWARD);
  _motorRight->run(BACKWARD);
}

void DifferentialDrive::stop()
{
  _motorLeft->run(RELEASE);
  _motorRight->run(RELEASE);
}

int DifferentialDrive::mapPercentageToPwm(float value)
{
  return map(value, 0,1, 0,255);
}

