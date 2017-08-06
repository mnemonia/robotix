#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int pirState = LOW;             // we start, assuming no motion detected
int inputPin = 9;               // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(13,OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
}

void loop() {
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(13, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      myservo.attach(5);  // attaches the servo on pin 9 to the servo object
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      //digitalWrite(13,LOW);
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
        myservo.detach();  // attaches the servo on pin 9 to the servo object

    }
  } else {
    digitalWrite(13, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

