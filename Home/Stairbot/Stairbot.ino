int steps[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int stepCount = 12;

void setup()  {
  for(int i=0; i<stepCount; i++){
    out(steps[i]);
  } 
}

void fade()  { 
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    fadeTo(fadeValue);
    delay(30);                            
  } 
}

void fadeTo(int fadeValue){
  for(int i=0; i<stepCount; i++){
    analogWrite(steps[i], fadeValue);
  } 
}

void loop(){;}
