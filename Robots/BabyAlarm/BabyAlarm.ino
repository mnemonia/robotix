extern "C"{
#include "sTheUnit.h"
}

unsigned long time;
long sA;
long signalA;
long averageReadingA;
const int numberOfSamples =128;
const int middleValue = 340;
const int MAX_NOISE = 2000;
const int WAIT_TIME_IN_MILLIES = 15 * 1000; // 15 sec
int lastTimeSnapshotInMillies = 0;
int currentTimeInMillies;

void setup(){
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  /*********************************************************************
   * 	Execution of CIP Connector Activities
   *********************************************************************/

  /* Initializing CIP Machine */

  if (fINIT_())
  {
    /* activation of drive loop */
  }
  else 
  {
    /* initialization failed, abort drive */
  }
}
void loop(){
  if(currentNoise() > maxAllowedNoise()){
    Serial.println("Loud");
    IN_.Surveillance(C1_Loud);
  }
  else{
    Serial.println("Silent");
    IN_.Surveillance(C1_Silent);
  }
  
  if(isRecordButtonPressed()){
    IN_.Record(C3_Recording); 
  }else{
    IN_.Record(C3_Done);    
  }
  delay(2000);
}

long currentNoise(){
  long noise = map(senseSound(),24000,50000,0,100);
  Serial.print("Noise: ");
  Serial.println(noise);
  return noise;
}

long senseSound(){
  return average(A0);  
}

long maxAllowedNoise(){
  long treshold = map(senseThreshold(),0,1023,0,100);
  Serial.print("Treshold: ");
  Serial.println(treshold);
  return treshold;
}

long senseThreshold(){
  return analogRead(A1);  
}

long average(int pin){
  long sumOfSquaresA = 0;
  for(int i=0; i<numberOfSamples; i++){
    sA = analogRead(pin);
    signalA = (sA - middleValue);
    signalA *= signalA;
    sumOfSquaresA += signalA;
  }
  return sumOfSquaresA / numberOfSamples; 
}

boolean isRecordButtonPressed(){
  return digitalRead(11) > 0;  
}





