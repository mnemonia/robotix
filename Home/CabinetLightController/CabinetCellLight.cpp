#include "Arduino.h"
#include "CabinetCellLight.h"

CabinetCellLight::CabinetCellLight(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _fadeSpeed = 150;
}

void CabinetCellLight::fadeOut()
{
  for(int i=_fadeSpeed-1; i>=0; i--){
    analogWrite(_pin, i);
    delay(5);
  }
}

void CabinetCellLight::fadeIn()
{
  for(int i=0; i<_fadeSpeed; i++){
    analogWrite(_pin, i);
    delay(25);
  }
}
