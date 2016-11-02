// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = A7;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(A7, INPUT);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(13, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  hello();
  //enter();
  //show();
  //leave(); 
}

void hello(){
  on();
  delay(100);
  off();
  delay(300);
  on();
  delay(300);
  off();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = analogRead(buttonPin);
  if(buttonState > 300){
    buttonState = HIGH;
  }else{
    buttonState = LOW;
  }
  //Serial.println(analogRead(buttonPin));
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    // turn LED on:
    enter();
    show();
    leave();
    //digitalWrite(ledPin, HIGH);
    //digitalWrite(13, HIGH);
    //delay(30000);
    //digitalWrite(ledPin, LOW);
    //digitalWrite(13, LOW);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    digitalWrite(13, LOW);
  }
  delay(50);
}

void enter(){
  on();
  delay(60);
  off();  
  delay(510);
  on();
  delay(90);
  off();  
  delay(650);
  on();
  delay(220);
  off();  
  delay(440);
  on();
  delay(620);
  off();  
  delay(60);
  on();
  delay(90);
  off();  
  delay(110);
  on();
  delay(30);
  off();  
  delay(60);
  on();
  delay(420);
  off();  
  delay(110);
  on();
  delay(1000);
  off();  
  delay(160);
  on();
  delay(1100);
  off();  
}
void show(){
  on();
  delay(30000);
  off();  
}
void leave(){
  off();  
  delay(160);
  on();
  delay(1600);
  off();  
  delay(160);
  on();
  delay(800);
  off();  
  delay(160);
  on();
  delay(200);
  off();  
}
  
void on(){
  digitalWrite(ledPin, HIGH);
    digitalWrite(13, HIGH);
}
void off(){
  digitalWrite(ledPin, LOW);
    digitalWrite(13, LOW);
}



