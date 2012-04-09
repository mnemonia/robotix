#include <Stepper.h>

const int ZERO_TO_ONE_STEPS = 2;
const int stepsPerRevolution = 360;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 6,7);            

void setup() {
  myStepper.setSpeed(90);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  for(int i=1; i<=10; i++){
    rotateFwd(i*ZERO_TO_ONE_STEPS);
    delay(4000);
    rotateBwd(i*ZERO_TO_ONE_STEPS);
    delay(1000);
  }
}

void rotateFwd(int steps){
   for(int i=0; i<steps; i++){
      myStepper.step(-stepsPerRevolution);
   }
}
void rotateBwd(int steps){
   for(int i=0; i<steps; i++){
      myStepper.step(stepsPerRevolution);
   }
}


