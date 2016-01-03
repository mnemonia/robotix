#include "Arduino.h"

class LightSwitch {
  public:
    LightSwitch(int switchPin);
    boolean isOn();

  private:
    int _switchPin;
    boolean _isOn;
};
