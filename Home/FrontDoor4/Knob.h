#include "Arduino.h"

class Knob {
  public:
    Knob(int pin);
    boolean isDown(); 
  private:
    int _pin; 
};
