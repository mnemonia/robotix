#ifndef FindlingTouchToggleButton_h
#define FindlingTouchToggleButton_h

#include "Arduino.h"

class FindlingTouchToggleButton
{
  public:
    FindlingTouchToggleButton(int pin);
    boolean isOn();
    void printState();

  private:
    int _pin;
    boolean _isOn;
    int _buttonState;             // the current reading from the input pin
    int _lastButtonState;   // the previous reading from the input pin
    long _lastDebounceTime;  // the last time the output pin was toggled
    long _debounceDelay;    // the debounce time; increase if the output flickers    
};

#endif

