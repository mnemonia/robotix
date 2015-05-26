#ifndef FindlingDoorController_h
#define FindlingDoorController_h

#include "FindlingMagnetDoorLock.h"
#include "FindlingNeoPixel.h"
#include "Arduino.h"

class FindlingDoorController
{
  public:
    FindlingDoorController(
        int doorLockPin, 
        int lightPin, 
        int i_redStart,
        int i_redEnd,
        int i_greenStart,
        int i_greenEnd,
        int i_blueStart,
        int i_blueEnd);
    void checkAndSetLight();
    void update();
    void shut();
    void printState();
  private:
    FindlingMagnetDoorLock _lock;  
    FindlingNeoPixel _light;  
};

#endif

