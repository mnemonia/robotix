const int lightSwitchPin = 5;
// Pump Settings

const int pumpFwdDirectionPin = 8;
const int pumpBwdDirectionPin = 11;
const int pumpSpeedPin = 9;
/*
const int pumpFwdDirectionPin = 12;
const int pumpBwdDirectionPin = 13;
const int pumpSpeedPin = 10;
*/
const int pumpSpeed = 255;
boolean isDoorOpen = false;

void setup() {
  Serial.begin(9600);
  init(pumpFwdDirectionPin);
  init(pumpBwdDirectionPin);
  init(pumpSpeedPin);
  pinMode(lightSwitchPin,OUTPUT);
  off(pumpFwdDirectionPin);
  on(pumpBwdDirectionPin);
}

void loop() {
  int isOn = digitalRead(lightSwitchPin);
  Serial.println(isOn);
  if(isOn==1 && !isDoorOpen){
    isDoorOpen = true;
    fadeIn();
  }else if(isOn==0 && isDoorOpen){
    isDoorOpen = false;
    fadeOut();  
  }
}

void fadeIn(){
  for(int i=0; i<pumpSpeed; i++){
    analogWrite(pumpSpeedPin, i);
    delay(25);
  }
}

void fadeOut(){
  for(int i=pumpSpeed-1; i>=0; i--){
    analogWrite(pumpSpeedPin, i);
    delay(5);
  }
}

void on(int pin){
  digitalWrite(pin,HIGH);
}

void off(int pin){
  digitalWrite(pin,LOW);
}

void init(int pin){
  pinMode(pin,OUTPUT);
}

