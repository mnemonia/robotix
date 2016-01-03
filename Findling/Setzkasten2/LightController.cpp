#include "Arduino.h"
#include "LightController.h"

LightController::LightController(int ldrPin, int ledPin)
{
  pinMode(ledPin, OUTPUT);
  _ldrPin = ldrPin;
  _ledPin = ledPin;
  _currentLdrValue = 0;
  _lastLedValue = 0;
}

void LightController::tick(){
  int ledValue = mapLdrValueToLedValue(analogRead(_ldrPin));
//  Serial.print(_lastLedValue);
//  Serial.print(" ");
//  Serial.println(ledValue);
  if(ledValue == _lastLedValue){
    return;
  }
  
  if(ledValue < _lastLedValue){
  Serial.println("down");
    dimDown(ledValue);
  }else if(ledValue > _lastLedValue){
  Serial.println("up");
    dimUp(ledValue);
  }    
}

void LightController::off(){
  if(_lastLedValue == 0){
    return;
  }
  if(_lastLedValue > 100){
    _lastLedValue -= 50;
    analogWrite(_ledPin, _lastLedValue);
  }
  dimDown(0);
}

void LightController::dimUp(int ledValue){
  for(int i = _lastLedValue; i <= ledValue; i++){
    analogWrite(_ledPin, i);
    delay(20);
  }
  _lastLedValue = ledValue;
}
void LightController::dimDown(int ledValue){
  for(int i = _lastLedValue; i >= ledValue; i--){
    analogWrite(_ledPin, i);
    delay(20);
  }
  _lastLedValue = ledValue;
}

int LightController::mapLdrValueToLedValue(int value){
  //Serial.println(value);
  if(value < 150){
    return 75;
  }
  if(value < 450){
    return 125;
  }
  if(value < 900){
    return 180;
  }
  if(value < 1025){
    return 255;
  }
  return 255;
}

