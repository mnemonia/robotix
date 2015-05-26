#ifndef FindlingMagnetDoorLock_h
#define FindlingMagnetDoorLock_h

#include "Arduino.h"

class FindlingMagnetDoorLock
{
  public:
    FindlingMagnetDoorLock(int pin);
    boolean isOpen();
    void printState();
  private:
    int _pin;
};

#endif

