#include "FindlingMagnetDoorLock.h"

FindlingMagnetDoorLock::FindlingMagnetDoorLock(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

boolean FindlingMagnetDoorLock::isOpen()
{
  return digitalRead(_pin) == HIGH;
}

void FindlingMagnetDoorLock::printState()
{
  Serial.print("State: ");
  Serial.print("isOpen:");
  Serial.println(isOpen());
}

