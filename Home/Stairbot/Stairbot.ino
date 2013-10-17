int steps[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45};
int stepCount = 14;
boolean allTogether = true;

void setup()  {
  initializeLights();
  if(allTogether){
    fadeAllTogether();
  }else{
    fadeTopDownAndBottomUpAndMeetInTheMiddle();
  }
}

void initializeLights(){
  for(int i=0; i<stepCount; i++){
    out(steps[i]);
  } 
}

void fadeAllTogether()  { 
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    fadeAllToNext(fadeValue);
    delay(30);                            
  } 
}

void fadeAllToNext(int fadeValue){
  for(int i=0; i<stepCount; i++){
    analogWrite(steps[i], fadeValue);
  } 
}

void out(int pin){
  pinMode(pin, OUTPUT);
}

void loop(){;}

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
