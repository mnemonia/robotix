const int fadeSpeed = 150;
// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin
const int indicatorPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
boolean isOn = false;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  pinMode(indicatorPin, OUTPUT);      
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && !isOn) {     
    digitalWrite(indicatorPin, HIGH);  
//    digitalWrite(ledPin, HIGH);  
    fadeIn();
    isOn = true;
  } 
  else if(buttonState == LOW && isOn) {
    digitalWrite(indicatorPin, LOW);  
//    digitalWrite(ledPin, LOW); 
    fadeOut();
    isOn = false;
  }
}

/*
const int lightSwitchPin = 5;
// Pump Settings

const int pumpFwdDirectionPin = 8;
const int pumpBwdDirectionPin = 11;
const int pumpSpeedPin = 9;
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
*/
void fadeIn(){
  for(int i=0; i<fadeSpeed; i++){
    analogWrite(ledPin, i);
    delay(25);
  }
}

void fadeOut(){
  for(int i=fadeSpeed-1; i>=0; i--){
    analogWrite(ledPin, i);
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

