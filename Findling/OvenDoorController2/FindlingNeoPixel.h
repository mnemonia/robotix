#ifndef FindlingNeoPixel_h
#define FindlingNeoPixel_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class FindlingNeoPixel
{
  public:
    FindlingNeoPixel(
        int pin, 
        int i_redStart,
        int i_redEnd,
        int i_greenStart,
        int i_greenEnd,
        int i_blueStart,
        int i_blueEnd);
    void turnOn();
    void turnOff();
    void update();
    void printState();
  private:
    Adafruit_NeoPixel pixels;
    int _pin;
    long ioTime;    // milliseconds of off-time
    unsigned long previousMillis;  	// will store last time LED was updated
    int t;
    int redStart;
    int redEnd;
    int greenStart;
    int greenEnd;
    int blueStart;
    int blueEnd;      
    boolean isTurningOn;
    boolean isOn;
    boolean isTurningOff;
    boolean isOff;
    
    int nextColor(int colorStart, int colorEnd, int t);
};

#endif

