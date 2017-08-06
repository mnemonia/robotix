#include "DifferentialDrive.h"

int leftMotorPort = 1;
int rightMotorPort = 2;
DifferentialDrive drive(leftMotorPort, rightMotorPort);

void setup() {
  drive.setup();
}

void loop() {
  drive.forward();
  delay(4000);
  
  drive.stop();
  delay(1000);
  
  drive.backward();
  delay(4000);
  
  drive.stop();
  delay(2000);

  // Add more motion to the robot using the above principle

}
