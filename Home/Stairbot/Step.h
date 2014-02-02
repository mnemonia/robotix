#ifndef Step_h
#define Step_h

#include "Arduino.h"

class Step
{
  public:
    Step(int pin);
    void fadeTo(int value);
    void on();
    void off();
  private:
    int _pin;
};

#endif
