/* Raw IR commander
 
 This sketch/program uses the Arduno and a PNA4602 to 
 decode IR received.  It then attempts to match it to a previously
 recorded IR signal
 
 Code is public domain, check out www.ladyada.net and adafruit.com
 for more tutorials! 
 */

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN      PIND
#define IRpin          2

// the maximum pulse 65000 we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 4178

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20


//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//holder for infromation you're going to pass to shifting function
byte data = 0; 

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "ircodesSilverlitPico2006.h"

void setup(void) {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
}

void loop(void) {
  int numberpulses;
  
  numberpulses = listenForIR();
  
  Serial.print("Heard ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");
  if(numberpulses<21){return;}
  
  if (IRcompare(numberpulses, IRsignal_LEFT_ChannelA)) {
    Serial.println("BWD");
    backward();
  }

  if (IRcompare(numberpulses, IRsignal_RIGHT_ChannelA)) {
    Serial.println("FWD");
    forward();
  }

  if (IRcompare(numberpulses, IRsignal_FORWARD_FULL_ChannelA)) {
    Serial.println("PLAY");
    play();
  }
  
  if (IRcompare(numberpulses, IRsignal_FORWARD_MEDIUM_ChannelA)) {
    Serial.println("PLAY");
    //play();
  }

  if (IRcompare(numberpulses, IRsignal_STOP_ChannelA)) {
    Serial.println("STOP");
//    randomBehaviorCommand();
pause();
  }

}

void reset(){
 // pause();
}

boolean IRcompare(int numpulses, int Signal[]) {
  
  for (int i=0; i< numpulses-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    
    /*
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
    */
    
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
    
    /*
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
    */
    
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
    
    //Serial.println();
  }
  // Everything matched!
  return true;
}

int listenForIR(void) {
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
  
//  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH

       // count off another few microseconds
       highpulse++;
       delayMicroseconds(RESOLUTION);

       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
  
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
       delayMicroseconds(RESOLUTION);
       if ((lowpulse >= MAXPULSE)  && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
  }
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
  
  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");
}

void backward(){
  fromRightToLeftFast();
}
void forward(){
  fromLeftToRightFast();
}
void play(){
  fromLeftToRightSlow();
}
void pause(){
  blinkAll_2Bytes(1,500); 
}
void randomBehaviorCommand(){
  pause();
  play();
  forward();
  play();
  backward();
  play();
  pause();
}

void fromLeftToRightSlow(){
  fromLeftToRight(200);
}
void fromLeftToRightFast(){
  fromLeftToRight(40);
}
void fromRightToLeftSlow(){
  fromRightToLeft(200);
}
void fromRightToLeftFast(){
  fromRightToLeft(40);
}
void fromLeftToRight(int delayValue){
  // light each pin one by one using a function A
  for (int j = 0; j < 8; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //red LEDs
    lightShiftPinA(7-j);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    delay(delayValue);
  }
}
void fromRightToLeft(int delayValue){
  // light each pin one by one using a function A
  for (int j = 0; j < 8; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //red LEDs
    lightShiftPinB(j);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    delay(delayValue);
  } 
}

//This function uses bitwise math to move the pins up
void lightShiftPinA(int p) {
  //defines a local variable
  int pin;

  //this is line uses a bitwise operator
  //shifting a bit left using << is the same
  //as multiplying the decimal number by two. 
  pin = 1<< p;

  //move 'em out
  shiftOut(dataPin, clockPin, pin);   

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


//blinks both registers based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}
