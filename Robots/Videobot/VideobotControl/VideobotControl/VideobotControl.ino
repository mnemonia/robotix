#define PLAY 0xEF50AF
#define STOP 0xEF40BF
#define FWD 0xEF0AF5
#define BWD 0xEF2AD5

#define IR_SIGNAL_COUNT 1
#define JUMP_DELAY 1000

#include <IRremote.h>

IRsend irsend;

const int FWD_IDLE_PIN = 7;
const int FWD_ACTIVE_PIN = 2;
const int BWD_IDLE_PIN = 4;
const int BWD_ACTIVE_PIN = 5;
const int ON_PIN = 6;

const int treshold = 600;


void setup() {         
Serial.begin(9600);  
  pinMode(FWD_IDLE_PIN, OUTPUT);     
  pinMode(FWD_ACTIVE_PIN, OUTPUT);     
  pinMode(BWD_IDLE_PIN, OUTPUT);     
  pinMode(BWD_ACTIVE_PIN, OUTPUT);     
  pinMode(ON_PIN, OUTPUT);     
  pinMode(A0, INPUT);     
  pinMode(A1, INPUT);     
  digitalWrite(ON_PIN, HIGH);   // set the LED on
}
void loop() {
  int fwdControl = analogRead(A0);
  Serial.print("FWD Control on AO: ");
  Serial.println(fwdControl);
  int bwdControl = analogRead(A1);
  Serial.print("BWD Control on A1: ");
  Serial.println(bwdControl);

  if(fwdControl > treshold && bwdControl > treshold){
    play();
  }
  if(fwdControl < treshold && bwdControl > treshold){
    fwd();
    delay(JUMP_DELAY);
  }
  if(fwdControl > treshold && bwdControl < treshold){
    bwd();
    delay(JUMP_DELAY);
  }
  delay(50);
}

void play(){
  Serial.println("Play");
  sendPlayCommand();
  digitalWrite(FWD_IDLE_PIN, HIGH);   // set the LED on
  digitalWrite(FWD_ACTIVE_PIN, LOW);   // set the LED on
  digitalWrite(BWD_IDLE_PIN, HIGH);   // set the LED on
  digitalWrite(BWD_ACTIVE_PIN, LOW);   // set the LED on
}
void fwd(){
  Serial.println("FWD");
  sendFwdCommand();
  digitalWrite(FWD_IDLE_PIN, LOW);   // set the LED on
  digitalWrite(FWD_ACTIVE_PIN, HIGH);   // set the LED on
  digitalWrite(BWD_IDLE_PIN, HIGH);   // set the LED on
  digitalWrite(BWD_ACTIVE_PIN, LOW);   // set the LED on  
}
void bwd(){
  Serial.println("BWD");
  sendBwdCommand();
  digitalWrite(FWD_IDLE_PIN, HIGH);   // set the LED on
  digitalWrite(FWD_ACTIVE_PIN, LOW);   // set the LED on
  digitalWrite(BWD_IDLE_PIN, LOW);   // set the LED on
  digitalWrite(BWD_ACTIVE_PIN, HIGH);   // set the LED on
}

void sendPlayCommand() {
  for (int i = 0; i < IR_SIGNAL_COUNT; i++) {
    irsend.sendNEC(0xEF50AF, 32); 
    delay(100);
  }
}
void sendFwdCommand() {
  for (int i = 0; i < IR_SIGNAL_COUNT; i++) {
    irsend.sendNEC(FWD, 32); 
    delay(100);
  }
}
void sendBwdCommand() {
  for (int i = 0; i < IR_SIGNAL_COUNT; i++) {
    irsend.sendNEC(BWD, 32); 
    delay(100);
  }
}

