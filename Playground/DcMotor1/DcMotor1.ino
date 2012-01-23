#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

int theSpeed = 100;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor 1 test!");
  
  motor.setSpeed(theSpeed);     // set the speed to 200/255
  motor2.setSpeed(theSpeed);     // set the speed to 200/255
}

void loop() {
  forward();
  delay(2000);
  turn();
  delay(500);
}

void forward(){
  motor.run(FORWARD);      // turn it on going forward
  motor2.run(FORWARD);      // turn it on going forward
}

void turn(){
  motor.run(RELEASE);      // turn it on going forward
  motor2.run(FORWARD);      // turn it on going forward
}
