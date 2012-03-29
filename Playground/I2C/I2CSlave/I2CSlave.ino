#include <Wire.h>

#define LED_PIN 13
#define LED_1 12
#define LED_2 11

int x;

void setup() {
  Wire.begin(0x21);                // Start I2C Bus as a Slave (Device Number 9)
  Wire.onReceive(receiveEvent); // register event
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  
  x = 0;
}

void loop() {
  //If value received is 0 blink LED 1
  if (x == 5) {
    digitalWrite(LED_1, HIGH);
    delay(200);
    digitalWrite(LED_1, LOW);
    delay(200);
  }
}

void receiveEvent(int howMany) {
  x = Wire.read();    // receive byte as an integer
}

