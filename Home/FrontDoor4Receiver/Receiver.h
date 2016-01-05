#include "Arduino.h"

class Receiver {
  public:
    Receiver(int pin);
    boolean isOn();   
  private:
    int _pin;
};
