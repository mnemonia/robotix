#include <VirtualWire.h>
#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
const int FWD = 111;
const int BWD = 112;
const int LEFT = 211;
const int RIGHT = 212;
int heading = FWD;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_3 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

const int TRESHOLD = 1000;

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
}

void loop()                    
{
    long start = millis();
    if(cs_4_2.capacitiveSensor(30) > TRESHOLD){
      forward();
    }
    if(cs_4_6.capacitiveSensor(30) > TRESHOLD){
      backward();
    }
    if(cs_4_5.capacitiveSensor(30) > TRESHOLD){
      left();
    }
    if(cs_4_3.capacitiveSensor(30) > TRESHOLD){
      right();
    }
    delay(50);                             // arbitrary delay to limit data to serial port 
}

void forward()
{
  if(heading==FWD){
    return;
  }
  heading==FWD;
  
    const char *msg = "f";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
}
void backward()
{
  if(heading==BWD){
    return;
  }
  heading==BWD;
  
    const char *msg = "b";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
}
void left()
{
  if(heading==LEFT){
    return;
  }
  heading==LEFT;

    const char *msg = "l";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
}
void right()
{
  if(heading==RIGHT){
    return;
  }
  heading==RIGHT;
  
    const char *msg = "r";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
}
