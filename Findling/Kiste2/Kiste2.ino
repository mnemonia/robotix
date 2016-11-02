// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 9;    // the number of the pushbutton pin
const int ledPin = 6;      // the number of the LED pin

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int MAX = 255;
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, LOW);
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

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        ledState = !ledState;
        if(ledState){
          // fade in from min to max in increments of 5 points:
          for (int fadeValue = 0 ; fadeValue <= MAX; fadeValue += 5) {
            // sets the value (range from 0 to MAX):
            analogWrite(ledPin, fadeValue);
            // wait for 30 milliseconds to see the dimming effect
            delay(30);
          }
        }else{
          // fade out from max to min in increments of 5 points:
          for (int fadeValue = MAX ; fadeValue >= 0; fadeValue -= 5) {
            // sets the value (range from 0 to MAX):
            analogWrite(ledPin, fadeValue);
            // wait for 30 milliseconds to see the dimming effect
            delay(30);
          }
        }
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}

