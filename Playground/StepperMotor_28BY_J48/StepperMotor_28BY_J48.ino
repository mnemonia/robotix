#include <Stepper.h>

const int stepsPerRevolution = 360;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 6,7);            

void setup() {
  myStepper.setSpeed(165);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
   rotate360();
   rotate360CC();

   delay(2000);
}

void rotate360(){
  // step one revolution  in one direction:
   Serial.println("clockwise");
   for(int i=0; i<22; i++){
      myStepper.step(stepsPerRevolution);
   }
}
void rotate360CC(){
  // step one revolution  in one direction:
   Serial.println("counter-clockwise");
   for(int i=0; i<22; i++){
      myStepper.step(-stepsPerRevolution);
   }
}

