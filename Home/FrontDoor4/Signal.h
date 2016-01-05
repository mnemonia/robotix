#include "Arduino.h"

class Signal {
  public:
    Signal(int pin);
    void sendSignal(int millies);
  private:
    int _pin;  
};
