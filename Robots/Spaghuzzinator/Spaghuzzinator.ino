#include <Servo.h> 

Servo headServo;
//Servo pitchServo;
int pos = 0;    // variable to store the servo position 

const int leftRed = 4;
const int leftYellow = 8;
const int rightRed = 7;
const int rightYellow = 6;
const int center = 5;
//const int playPin = 9;
//const int recordPin = 10;
const int headServoPin = 11;

const int timerInMillies = 130;
const int servoTimerInMillies = 130;

const int servoCenterAngle = 90;
const int servoMaxAngle = 102;//175;//100;
const int servoMinAngle = 78;//20;//80;

char spaghuzzinatorIsHere[] = "... .--. .- --. .... ..- --.. --.. .. -. .- - --- .-.   .. ...   .... . .-. . ";
const int spaghuzzinatorIsHereCount = 79;

char youAreTerminated[] = "-.-- --- ..-   .- .-. .   - . .-. -- .. -. .- - . -.. ";
const int youAreTerminatedCount = 55;

char msgFaiSchifo[] = "..-. .- ..   ... -.-. .... .. ..-. --- ";
const int msgFaiSchifoCount = 40;

void setup() {     
  Serial.begin(9600);

  setupServo();

  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  out(leftRed);     
  out(leftYellow);     
  out(rightRed);     
  out(rightYellow);     
  out(center);     
  //out(playPin);     

  on(center);
  playTune();
  delay(2000);
}

void loop() {
// moveFromCenterToMax();
// moveFromMaxToCenter();

 moveFromCenterToMax();
//rotate();

  allOn();
  allOff();
//  sendSpaghuzzinatorIsHere();
  allOff();
  delay(2000);
  strobeShortAndFast(rightYellow);
  strobeShortAndFast(rightRed);
  allOn();

  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);

// rotate();
 moveFromMaxToCenter();

  delay(1000);              // wait for a second
  on(leftRed);
  off(leftYellow);
  on(rightRed);
  off(rightYellow);

//rotate();
moveFromCenterToMin();

  delay(1000);              // wait for a second
  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);

 moveFromMinToCenter();
//rotate();

 // sendYouAreTerminated();
  
  allOff();
  strobeLongAndSlow(rightRed);
  allOn();
moveFromCenterToMin();
//rotate();
  delay(1000);              // wait for a second

  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);
  strobeLongAndSlow(center);
  on(center);
  delay(400);              // wait for a second
  on(leftRed);
  off(leftYellow);
  on(rightRed);
  off(rightYellow);
  delay(400);              // wait for a second
moveFromMinToMax();
//rotate();
  delay(1000);              // wait for a second
moveFromMaxToMin();
//rotate();

  off(leftRed);
  off(leftYellow);
  off(rightRed);
  off(rightYellow);

//playTune();
//sendMsgFaiSchifo();  
moveFromMinToCenter();
//rotate();
  delay(1000);              // wait for a second
}

void sendSpaghuzzinatorIsHere(){
  int messagePin = rightYellow;
  off(messagePin);
  for(int pos = 0; pos < spaghuzzinatorIsHereCount; pos++){
    morse(spaghuzzinatorIsHere[pos], messagePin);
  }
}
void sendYouAreTerminated(){
  int messagePin = leftRed;  
  off(messagePin);
  for(int pos = 0; pos < youAreTerminatedCount; pos++){
    morse(youAreTerminated[pos], messagePin);
  }
}
void sendMsgFaiSchifo(){
  int messagePin1 = leftYellow;  
  int messagePin2 = rightRed;  
  off(messagePin1);
  off(messagePin2);
  for(int pos = 0; pos < msgFaiSchifoCount; pos++){
    morse(msgFaiSchifo[pos], messagePin1, messagePin2);
    morse(msgFaiSchifo[pos], messagePin1, messagePin2);
  }
}

void rotate() 
{ 
  headServo.attach(headServoPin);
  for(pos = 5; pos <= 175; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    headServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
delay(25);    
  for(pos = 175; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    headServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  headServo.detach();
} 

void playTune() {
//  digitalWrite(playPin, HIGH); 
//  delay(50);
//  digitalWrite(playPin, LOW);
}
void morse(char code, int messagePin){
  if(code=='.'){
    on(messagePin);
    delay(60);
    off(messagePin);
  }
  else if(code=='-'){
    on(messagePin);
    delay(120);
    off(messagePin);
  }
  else if(code==' '){
    off(messagePin);
    delay(240);
    off(messagePin);
  }
  delay(90);
}
void morse(char code, int messagePin1, int messagePin2){
  if(code=='.'){
    on(messagePin1);
    on(messagePin2);
    delay(60);
    off(messagePin1);
    off(messagePin2);
  }
  else if(code=='-'){
    on(messagePin1);
    on(messagePin2);
    delay(120);
    off(messagePin1);
    off(messagePin2);
  }
  else if(code==' '){
    off(messagePin1);
    off(messagePin2);
    delay(240);
    off(messagePin1);
    off(messagePin2);
  }
  delay(90);
}
void out(int pin){
  pinMode(pin,OUTPUT);
}
void on(int pin){
  digitalWrite(pin,HIGH);
}
void off(int pin){
  digitalWrite(pin,LOW);
}

void toggleFaster(int pinOne, int pinTwo){

}

void strobeShortAndSlow(int pin){
  strobeShort(pin, 250);
}
void strobeShortAndFast(int pin){
  strobeShort(pin, 150);
}
void strobeLongAndSlow(int pin){
  strobeLong(pin, 250);
}
void strobeLongAndFaster(int pin){
  strobeLong(pin, 100);
}
void strobeLong(int pin, int strobeDelay){
  strobe(pin,strobeDelay, 10);
}
void strobeShort(int pin, int strobeDelay){
  strobe(pin,strobeDelay, 5);
}
void strobe(int pin, int strobeDelay, int strobeCount){
  for(int i=0; i<strobeCount; i++){
    on(pin);
    delay(strobeDelay);
    off(pin);
    delay(strobeDelay);
  }
}

void allOff(){
  off(leftRed);
  off(leftYellow);
  off(rightRed);
  off(rightYellow);
}
void allOn(){
  on(leftRed);
  on(leftYellow);
  on(rightRed);
  on(rightYellow);
}
void moveFromMaxToCenter(){
  headServo.attach(headServoPin);
   for(pos = servoMaxAngle; pos >= servoCenterAngle; pos -= 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   headServo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}
void moveFromMinToMax(){
  headServo.attach(headServoPin);
  // move();
   for(pos = servoMinAngle; pos <= servoMaxAngle; pos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
     headServo.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}
void moveFromCenterToMax(){
  headServo.attach(headServoPin);
  // move();
   for(pos = servoCenterAngle; pos <= servoMaxAngle; pos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
     headServo.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}
void moveFromMinToCenter(){
  headServo.attach(headServoPin);
  // move();
   for(pos = servoMinAngle; pos <= servoCenterAngle; pos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
     headServo.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}
void moveFromMaxToMin(){
  headServo.attach(headServoPin);
   for(pos = servoMaxAngle; pos >= servoMinAngle; pos -= 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   headServo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}
void moveFromCenterToMin(){
  headServo.attach(headServoPin);
   for(pos = servoCenterAngle; pos >= servoMinAngle; pos -= 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   headServo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(servoTimerInMillies);                       // waits 15ms for the servo to reach the position 
   } 
  headServo.detach();
}

void stopMove(){
  headServo.detach();
}

void setupServo(){  
  headServo.attach(headServoPin);
  headServo.write(servoCenterAngle); 
}

void wait(){
  delay(timerInMillies);
}

void waitLong(){
  delay(5*timerInMillies);
}











