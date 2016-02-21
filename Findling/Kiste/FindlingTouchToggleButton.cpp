#include "FindlingTouchToggleButton.h"

FindlingTouchToggleButton::FindlingTouchToggleButton(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _isOn = false;
  _buttonState = HIGH;
  _lastButtonState = LOW;
  _lastDebounceTime = 0;
  _debounceDelay = 50;
}

boolean FindlingTouchToggleButton::isOn()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(_pin);
  // If the switch changed, due to noise or pressing:
  if (reading != _lastButtonState) {
    // reset the debouncing timer
    _lastDebounceTime = millis();
  }

  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != _buttonState) {
      _buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (_buttonState == LOW) {
        Serial.print("Toggle button state from ");
        Serial.print(_isOn);
        Serial.print(" to ");
        Serial.println(!_isOn);
        _isOn = !_isOn;
      }
    }

  }
  _lastButtonState = reading;
  
  return _isOn;
}

void FindlingTouchToggleButton::printState()
{
  Serial.print("State: ");
  Serial.print("_isOn:");
  Serial.println(isOn());
}

