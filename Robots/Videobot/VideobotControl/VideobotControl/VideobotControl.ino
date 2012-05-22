#include <IRremote.h>

IRsend irsend;

const int PLAY = 0xEF40BF;
const int STOP = 0xEF50AF;
const int FWD = 0xEF0AF5;
const int BWD = 0xEF2AD5;

void setup() {         
Serial.begin(9600);  
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(2, OUTPUT);     
  pinMode(3, OUTPUT);     
  pinMode(4, OUTPUT);     
  pinMode(5, OUTPUT);     
  pinMode(6, OUTPUT);     
  pinMode(7, OUTPUT);     
  pinMode(A0, INPUT);     
  pinMode(A1, INPUT);     
  digitalWrite(6, HIGH);   // set the LED on
  digitalWrite(7, HIGH);   // set the LED on
}

void play(){
  Serial.println("Play");
  sendCommand(PLAY);
  digitalWrite(2, HIGH);   // set the LED on
  digitalWrite(3, LOW);   // set the LED on
  digitalWrite(4, HIGH);   // set the LED on
  digitalWrite(5, LOW);   // set the LED on
}
void fwd(){
  Serial.println("FWD");
  sendCommand(FWD);
  digitalWrite(2, LOW);   // set the LED on
  digitalWrite(3, HIGH);   // set the LED on
  digitalWrite(4, HIGH);   // set the LED on
  digitalWrite(5, LOW);   // set the LED on
}
void bwd(){
  Serial.println("BWD");
  sendCommand(BWD);
  digitalWrite(2, HIGH);   // set the LED on
  digitalWrite(3, LOW);   // set the LED on
  digitalWrite(4, LOW);   // set the LED on
  digitalWrite(5, HIGH);   // set the LED on
}
void loop() {
  int fwdControl = analogRead(A0);
  Serial.print("FWD Control on AO: ");
  Serial.println(fwdControl);
  int bwdControl = analogRead(A1);
  Serial.print("BWD Control on A1: ");
  Serial.println(bwdControl);
  if(fwdControl > 500 && bwdControl > 500){
    play();
  }
  if(fwdControl < 500 && bwdControl > 500){
    fwd();
  }
  if(fwdControl > 500 && bwdControl < 500){
    bwd();
  }
  delay(50);              // wait for a second
}

void sendCommand(int command) {
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(command, 32); 
    delay(100);
  }
}
