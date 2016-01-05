#include "Arduino.h"
#include <Servo.h>

class Bell{
  public:
    Bell(int pin);
    void ring();
  private:
    void left();
    void right();
    Servo myservo;
    int _pin;  
    int _pos;
};
