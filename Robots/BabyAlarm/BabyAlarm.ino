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
    Serial.println("A");
    IN_.Surveillance(C1_Loud);
  }
  else{
    Serial.println("B");
    IN_.Surveillance(C1_Silent);
  }
  delay(2000);
}

long currentNoise(){
  long noise = senseSound();
  Serial.print("Noise: ");
  Serial.println(noise);
  return noise;
}

long maxAllowedNoise(){
  long treshold = senseThreshold();
  Serial.print("Treshold: ");
  Serial.println(treshold);
  return treshold;
}

long senseSound(){
  return average(A0);  
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





