#include <SoftwareServo.h>

SoftwareServo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int currentPosition = 90;

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

#define FWD_PIN 13
#define LEFT_PIN 12
#define RIGHT_PIN 11
#define STOP_PIN 10

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "ircodesSilverlitPico2006.h"


void setup() 
{ 
  
  initServo();
  initIrRemote();
}

void initServo(){
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.setMaximumPulse(2200);
  myservo.write(currentPosition);
  SoftwareServo::refresh();
} 


void initIrRemote() {
  pinMode(FWD_PIN, OUTPUT);        
  analogWrite(FWD_PIN,128);
  delay(1000);
  pinMode(FWD_PIN, OUTPUT);        
  analogWrite(FWD_PIN,255);
  delay(1000);
  digitalWrite(FWD_PIN,LOW);
  Serial.begin(9600);
  Serial.println("Ready to decode PicooZ IR!");  
}

void resceiveAndAct() {
  int numberpulses;

  numberpulses = listenForIR();

  Serial.print("Heard ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");
  if(numberpulses<21){
    return;
  }

  if (IRcompare(numberpulses, IRsignal_LEFT_ChannelA)) {
    Serial.println("LEFT");
    reset();
   for(int i = currentPosition; i < 170; i += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(i);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
      SoftwareServo::refresh();
    } 
    currentPosition = 170;
  }

  if (IRcompare(numberpulses, IRsignal_RIGHT_ChannelA)) {
    Serial.println("RIGHT");
    reset();
    for(int i = currentPosition; i>=10; i-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(i);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
      SoftwareServo::refresh();
    } 
    currentPosition = 10;
  }

  if (IRcompare(numberpulses, IRsignal_FORWARD_FULL_ChannelA)) {
    Serial.println("FORWARD FAST");
    reset();
    digitalWrite(FWD_PIN, HIGH);   // set the LED on
  }

  if (IRcompare(numberpulses, IRsignal_FORWARD_MEDIUM_ChannelA)) {
    Serial.println("FORWARD MEDIUM");
    reset();
    digitalWrite(FWD_PIN, HIGH);   // set the LED on
  }

  if (IRcompare(numberpulses, IRsignal_STOP_ChannelA)) {
    Serial.println("STOP");
  //  reset();
    digitalWrite(STOP_PIN, HIGH);   // set the LED on
  }
SoftwareServo::refresh();
}

void reset(){
  digitalWrite(FWD_PIN, LOW);   // set the LED off
  digitalWrite(LEFT_PIN, LOW);   // set the LED off
  digitalWrite(RIGHT_PIN, LOW);   // set the LED off
  digitalWrite(STOP_PIN, LOW);   // set the LED off
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
    } 
    else {
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
    } 
    else {
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

void loop() 
{ 
  resceiveAndAct();
} 


