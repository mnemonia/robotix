#include "FindlingDoorController.h"

FindlingDoorController::FindlingDoorController(        
        int buttonPin, 
        int lightPin, 
        int i_redStart,
        int i_redEnd,
        int i_greenStart,
        int i_greenEnd,
        int i_blueStart,
        int i_blueEnd)
: _button(buttonPin),
  _light(lightPin,i_redStart,i_redEnd,i_greenStart,i_greenEnd,i_blueStart,i_blueEnd)
{
}

void FindlingDoorController::checkAndSetLight()
{
  if(_button.isOn()){
    _light.turnOn();
  }else{
    _light.turnOff();
  }
}

void FindlingDoorController::update(){
  _light.update();
}
void FindlingDoorController::shut(){
  _light.off();
}
void FindlingDoorController::printState()
{
  _button.printState();
  _light.printState();
}

