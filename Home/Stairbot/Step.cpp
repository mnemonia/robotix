#include "Arduino.h"
#include "Step.h"

Step::Step(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Step::fadeTo(int value)
{
  analogWrite(_pin, value);
}

void Step::on()
{
  digitalWrite(_pin, HIGH);
}

void Step::off()
{
  digitalWrite(_pin, LOW);
}
