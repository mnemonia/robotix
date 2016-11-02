/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
boolean isOn = false;

int currentLightMaximum = 255;
int ambientLightRight = 0;
int ambientLightLeft = 0;
int ambientTresholdLow = 50;//150;
int ambientTresholdMid = 120;
int ambientTresholdHigh = 255;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

int readLdr(int pin) {
  return analogRead(pin);//map(analogRead(pin), 300, 1024, 0, 1024);
}
void loop() {
  ambientLightRight = readLdr(A0);
  ambientLightLeft = readLdr(A1);
  int ambientLight = max(ambientLightRight, ambientLightLeft);
  Serial.println(ambientLight);
  int currentLightValue = ambientLight;// ambientLight < 150 ? ambientTresholdLow : ambientLight < 800 ? ambientTresholdMid : ambientTresholdHigh;

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW && !isOn) {
    currentLightMaximum = currentLightValue;
    // turn LED on:
    isOn = true;
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= currentLightMaximum; fadeValue += 1) {
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(20);
    }
  }
  else if (buttonState == LOW && isOn) {
    // turn LED off:
    isOn = false;
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = currentLightMaximum ; fadeValue >= 0; fadeValue -= 1) {
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(20);
    }
  }
  else if (isOn) {
    if (currentLightValue > currentLightMaximum) {
      for (int fadeValue = currentLightValue ; fadeValue >= currentLightMaximum; fadeValue -= 1) {
        analogWrite(ledPin, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(20);
      }
      currentLightMaximum = currentLightValue;
    }
    if (currentLightValue < currentLightMaximum) {
      for (int fadeValue = currentLightMaximum ; fadeValue <= currentLightValue; fadeValue += 1) {
        analogWrite(ledPin, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(20);
      }
      currentLightMaximum = currentLightValue;
    }
  }
  delay(50);
}
