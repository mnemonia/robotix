#include "Stair.h"

Stair stair;

void setup()  {
  stair.fadeIn();
}

void loop(){;}

/*
void fadeTopDownAndBottomUpAndMeetInTheMiddle(){
  for(int i=0, j=stepCount-1; i<j; i++,j--){
    fadeTwoSteps(i,j);
  }
}

void fadeTwoSteps(int stepOne, int stepTwo){
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    analogWrite(steps[stepOne], fadeValue);
    analogWrite(steps[stepTwo], fadeValue);
    delay(30);                            
  } 
}
*/
