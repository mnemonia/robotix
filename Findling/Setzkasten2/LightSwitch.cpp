#include "LightSwitch.h"

LightSwitch::LightSwitch(int switchPin){
  pinMode(switchPin, INPUT);
  _switchPin = switchPin;
  _isOn = false;
};

boolean LightSwitch::isOn(){
  int switchState = digitalRead(_switchPin);
  if(switchState == LOW && !_isOn){
    _isOn = true;
  }else if(switchState == LOW && _isOn){
    _isOn = false;
  }
  return _isOn;
};
