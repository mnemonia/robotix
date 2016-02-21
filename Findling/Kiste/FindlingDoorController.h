#ifndef FindlingDoorController_h
#define FindlingDoorController_h

#include "FindlingTouchToggleButton.h"
#include "FindlingNeoPixel.h"
#include "Arduino.h"

class FindlingDoorController
{
  public:
    FindlingDoorController(
        int buttonPin, 
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
    FindlingTouchToggleButton _button;  
    FindlingNeoPixel _light;  
};

#endif

