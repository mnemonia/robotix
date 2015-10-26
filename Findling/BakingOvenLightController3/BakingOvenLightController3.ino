#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t currstate = 0;
uint8_t touchThreshold = 2;//12;
uint8_t releaseThreshold = 6;
bool isOn = false;

int ledPin = 9;    // LED connected to digital pin 9

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void blinkLeds() {
  analogWrite(ledPin, 100);
  delay(100);
  analogWrite(ledPin, 30);
  delay(50);
  analogWrite(ledPin, 100);
  delay(100);
  analogWrite(ledPin, 0);
}

void setup() {
  while (!Serial);        // needed to keep leonardo/micro from starting too fast!
  
  pinMode(13,OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("findl.ing baking oven controller"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  cap.setThreshholds(touchThreshold, releaseThreshold);
  Serial.println("MPR121 thresholds set");
  
  blinkLeds();
}

void lightsOn(){
  digitalWrite(13,HIGH);
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 10 ; fadeValue <= 255; fadeValue += 2) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void lightsOff(){
  digitalWrite(13,LOW);
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 200 ; fadeValue >= 0; fadeValue -= 2) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void loop() {
  currtouched = cap.touched();
  currtouched = currtouched & _BV(0);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (currtouched != lasttouched) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    if (currtouched) {
      Serial.print("touched and set ");
      Serial.println(isOn);
      if(!isOn){
        lightsOn();
        isOn = true;
      }else{
        lightsOff();
        isOn = false;
      }
    }
  }
lasttouched = currtouched;
delay(25);
}

void loopOld() {
  // Get the currently touched pads
  currtouched = cap.touched();
  if ((currtouched & _BV(0))) {
    Serial.print("touched and set ");
    Serial.println(isOn);
    if(!isOn){
      lightsOn();
      isOn = true;
    }else{
      lightsOff();
      isOn = false;
    }
  }
  // 50ms delay to fix on/off bug of sensor.
  delay(150);
  return;
    
  for (uint8_t i=0; i<1; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      if(!isOn){
        lightsOn();
        isOn = true;
      }else{
        lightsOff();
        isOn = false;
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched = currtouched;

  // 50ms delay to fix on/off bug of sensor.
  delay(150);
  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}


