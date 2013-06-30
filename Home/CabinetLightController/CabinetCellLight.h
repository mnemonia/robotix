#ifndef CabinetCellLight_h
#define CabinetCellLight_h

#include "Arduino.h"

class CabinetCellLight
{
  public:
    CabinetCellLight(int pin);
    void fadeIn();
    void fadeOut();
  private:
    int _pin;
    int _fadeSpeed;
    
};

#endif

