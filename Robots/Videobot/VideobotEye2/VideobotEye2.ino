#define PLAY 0xEF50AF
#define STOP 0xEF40BF
#define FWD 0xEF0AF5
#define BWD 0xEF2AD5

#define INTERVAL_PLAY 150
#define INTERVAL_FAST 60

#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

int currentMode = 0; // 0 for PLAY

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 10;

//holder for infromation you're going to pass to shifting function
byte data = 0; 

// Variables will change:
int currentLedState = LOW;
int currentLed = 0;             // ledState used to set the LED
int maxLed = 8;
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = INTERVAL_PLAY;           // interval at which to blink (milliseconds)

void setup()
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver

  on();
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if(PLAY == results.value){
      Serial.println("PLAY");
      currentMode = 0;
      interval = INTERVAL_PLAY;
    }else if(FWD == results.value){
      Serial.println("FWD");
      currentMode = 1;
      interval = INTERVAL_FAST;
    }else if(BWD == results.value){
      Serial.println("BWD");
      currentMode = 2;
      interval = INTERVAL_FAST;
    }
    irrecv.resume(); // Receive the next value
  }
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    on();
    next();
  }
}

void on(){
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);

  lightShiftPinB(currentLed);

  //return the latch pin high to signal chip that it 
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void next(){
  switch(currentMode){
    case 0:
    case 1:
      if(currentLed == 0){
        currentLed = maxLed - 1;
      }else{
        currentLed--;
      }
      break;
    case 2:
      if(currentLed == maxLed - 1){
        currentLed = 0;
      }else{
        currentLed++;
      }
      break;
  }
}

void increment(){
  if(currentLed < maxLed){
    currentLed++;
  }else{
    currentLed = 0;
  }
}

//This function uses that fact that each bit in a byte
//is 2 times greater than the one before it to
//shift the bits higher
void lightShiftPinB(int p) {
  //defines a local variable
  int pin;

  //start with the pin = 1 so that if 0 is passed to this
  //function pin 0 will light. 
  pin = 1;

  for (int x = 0; x < p; x++) {
    pin = pin * 2; 
  }
  //move 'em out
  shiftOut(dataPin, clockPin, pin);   
}

// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

