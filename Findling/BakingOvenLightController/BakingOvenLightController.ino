/*
 Debounce

 Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 a minimum delay between toggles to debounce the circuit (i.e. to ignore
 noise).

 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached from pin 2 to +5V
 * 10K resistor attached from pin 2 to ground

 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.


 created 21 November 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Limor Fried
 modified 28 Dec 2012
 by Mike Walters

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Debounce
 */
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 9;      // the number of the LED pin

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
bool isChanged = false;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int currentDimStep = 0;
int v;
int N = 21;
int A = 0;
int B = 254;
int X;

void dimUp() {
  for (currentDimStep = 0; currentDimStep < N; currentDimStep++) {
    v = currentDimStep / N;
    v = SMOOTHSTEP(v);
    X = (A * v) + (B * (1 - v));
    analogWrite( ledPin, X);
    delay(15);
  }
}

void dimDown() {
  for (currentDimStep = currentDimStep; currentDimStep > 0; currentDimStep--) {
    v = currentDimStep / N;
    v = SMOOTHSTEP(v);
    X = (B * v) + (A * (1 - v));
    analogWrite( ledPin, X);
    delay(15);
  }
}


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  blinkLeds();
}

void blinkLeds() {
  analogWrite(ledPin, 100);
  delay(100);
  analogWrite(ledPin, 30);
  delay(50);
  analogWrite(ledPin, 100);
  delay(100);
  analogWrite(ledPin, 0);
}
void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        ledState = !ledState;
        isChanged = true;
      }
    }
  }

  // set the LED:
  if (isChanged && ledState == HIGH) {
    for (int fadeValue = 10 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
    isChanged = false;
  } else if(isChanged && ledState == LOW) {
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 200 ; fadeValue >= 0; fadeValue -= 2) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
    isChanged = false;
  }
  //digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}

