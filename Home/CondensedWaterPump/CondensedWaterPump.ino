extern "C"{
#include "sCondensedWaterPumpUnit.h"
}

const int upperLevelSensorPin = A1;
const int lowerLevelSensorPin = A0;
const int upperLevelActorPin = 5;
const int lowerLevelActorPin = 6;
const int onIndicatorPin = 4;
const int runningPumpIndicatorPin = 3;
const int notRunningPumpIndicatorPin = 2;
int upperLevelSensorValue = -1;
int lowerLevelSensorValue = -1;

// Pump Settings
const int pumpFwdDirectionPin = 8;//11;
const int pumpBwdDirectionPin = 11;
const int pumpSpeedPin = 9;
const int pumpSpeed = 255;

const int waterIndicatorValue = 160;//25;

void setup(){
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  init(onIndicatorPin);
  init(runningPumpIndicatorPin);
  init(notRunningPumpIndicatorPin);


  init(upperLevelActorPin);
  init(lowerLevelActorPin);

  init(pumpFwdDirectionPin);
  init(pumpBwdDirectionPin);
  init(pumpSpeedPin);

  on(onIndicatorPin);
  off(runningPumpIndicatorPin);
  off(notRunningPumpIndicatorPin);

  if(!fINIT_()){
    // Fehler in fININT ...
  }
}

void checkUpperLevelSensor(){
  int value = getUpperLevelSensorValue();
  if(!hasUpperLevelSensorValueChanged(value)){
    return;
  }

  setUpperLevelSensorValue(value);
  switch(value){
  case LOW: 
    IN_.UpperLevelSensorInChan(C4_LOW);
    break;
  case HIGH:
    IN_.UpperLevelSensorInChan(C4_HIGH);
    break;
  }
}

void checkLowerLevelSensor(){
  int value = getLowerLevelSensorValue();
  if(!hasLowerLevelSensorValueChanged(value)){
    return;
  }
  
  setLowerLevelSensorValue(value);
  switch(value){
  case LOW: 
    IN_.LowerLevelSensorInChan(C3_LOW);
    break;
  case HIGH:
    IN_.LowerLevelSensorInChan(C3_HIGH);
    break;
  }
}

void setLowerLevelSensorValue(int value){
  lowerLevelSensorValue = value;
}
void setUpperLevelSensorValue(int value){
  upperLevelSensorValue = value;
}

void loop(){
  checkUpperLevelSensor();
  checkLowerLevelSensor();  
//  debug();
  delay(1000);  
}

void debug(){
  Serial.print("Upper Level Sensor Value: ");
  Serial.println(upperLevelSensorValue);
  Serial.print("Lower Level Sensor Value: ");
  Serial.println(lowerLevelSensorValue);
}


void on(int pin){
  digitalWrite(pin,HIGH);
}

void off(int pin){
  digitalWrite(pin,LOW);
}

void init(int pin){
  pinMode(pin,OUTPUT);
}

void startPump(){
  on(runningPumpIndicatorPin);
  off(notRunningPumpIndicatorPin);  
  analogWrite(pumpSpeedPin, pumpSpeed);
  on(pumpFwdDirectionPin);
  off(pumpBwdDirectionPin);
}

void stopPump(){
  off(runningPumpIndicatorPin);
  on(notRunningPumpIndicatorPin);  
  analogWrite(pumpSpeedPin, 0);
  off(pumpFwdDirectionPin);
  off(pumpBwdDirectionPin);
}

int getLowerLevelSensorValue(){
  // read the value from the sensor:
  on(lowerLevelActorPin);
  delay(40);
  int value = analogRead(lowerLevelSensorPin);    

  Serial.print("Lower Level Sensor Value: ");
  Serial.println(value);

  off(lowerLevelActorPin);
  return value < waterIndicatorValue ? HIGH : LOW;
}

int getUpperLevelSensorValue(){
  // read the value from the sensor:
  on(upperLevelActorPin);
  delay(40);
  int value = analogRead(upperLevelSensorPin);    
  off(upperLevelActorPin);

  Serial.print("Upper Level Sensor Value: ");
  Serial.println(value);
  
  return value < waterIndicatorValue ? HIGH : LOW;
}

boolean hasUpperLevelSensorValueChanged(int newValue){
  return newValue != upperLevelSensorValue;
}

boolean hasLowerLevelSensorValueChanged(int newValue){
  return newValue != lowerLevelSensorValue;
}




extern "C" {
  /*********************************************************************
   * 	User defined Output Channel Functions
   *********************************************************************/

  /* Output Channel Functions,
   	called by CIP Machine when a Message is written.
   	User defined function, with name to consider as suggestion */

  /* Parameters
   	name_		name value of message */

  void uCHAN_PumpOutChannel (unsigned char name_)
  {
    /* Accessing MESSAGE */
    switch (name_)
    {
    case C2_OFF:
      stopPump();
      break;
    case C2_ON:
      startPump();
      break;
    default: 
      break;
    }
  }

  /***bb.-******************************************************************
   * 	User defined Output Channel Interface Initialization Function
   *********************************************************************/

  void iCHAN_(void)
  {
    /* Initializing Input Error Function only if Input Error Option set */

#ifdef _EINPUT__
    IN_.EINPUT_ = uEINPUT_;
#endif 

    /* Initializing Output Interface */

    OUT_.PumpOutChannel = uCHAN_PumpOutChannel;
  }

}// extern "C"


