#include <Servo.h> 

Servo headServo;
//Servo pitchServo;
int pos = 0;    // variable to store the servo position 

const int leftRed = 4;
const int leftYellow = 8;
const int rightRed = 7;
const int rightYellow = 6;
const int center = 5;
const int headServoPin = 11;

const int timerInMillies = 130;
const int countSinusSquareLookupTableEntries = 62;
const int lookupTableCenter = countSinusSquareLookupTableEntries / 2;
int currentLookupTable = 10;

const int sinusSquareLookupTable90Plus10[] = {
  80, 80, 80, 80, 80, 80, 80, 81	,
  81, 81, 82, 82, 83, 84, 84, 85	,
  86, 86, 87, 88, 88, 89, 89, 89	,
  90, 90, 90, 90, 90, 90, 90, 90	,
  90, 90, 90, 90, 90, 91, 91, 91	,
  92, 92, 93, 94, 94, 95, 96, 96	,
  97, 98, 98, 99, 99, 99, 100, 100	,
  100, 100, 100, 100, 100, 100};

const int sinusSquareLookupTable90Plus5[] = {
  85, 85, 85, 85, 85, 85, 85, 85	,
  86, 86, 86, 86, 87, 87, 87, 88	,
  88, 88, 88, 89, 89, 89, 89, 90	,
  90, 90, 90, 90, 90, 90, 90, 90	,
  90, 90, 90, 90, 90, 90, 91, 91	,
  91, 91, 92, 92, 92, 93, 93, 93	,
  93, 94, 94, 94, 94, 95, 95, 95	,
  95, 95, 95, 95, 95, 95};

char spaghuzzinatorIsHere[] = "... .--. .- --. .... ..- --.. --.. .. -. .- - --- .-.   .. ...   .... . .-. . ";
const int spaghuzzinatorIsHereCount = 79;

char youAreTerminated[] = "-.-- --- ..-   .- .-. .   - . .-. -- .. -. .- - . -.. ";
const int youAreTerminatedCount = 55;

void sendSpaghuzzinatorIsHere(){
  int messagePin = rightYellow;
  for(int pos = 0; pos < spaghuzzinatorIsHereCount; pos++){
    morse(spaghuzzinatorIsHere[pos], messagePin);
  }
}
void sendYouAreTerminated(){
  int messagePin = leftRed;  
  for(int pos = 0; pos < youAreTerminatedCount; pos++){
    morse(youAreTerminated[pos], messagePin);
  }
}
void morse(char code, int messagePin){
  if(code=='.'){
    on(messagePin);
    delay(90);
    off(messagePin);
  }
  else if(code=='-'){
    on(messagePin);
    delay(180);
    off(messagePin);
  }
  else if(code==' '){
    off(messagePin);
    delay(360);
    off(messagePin);
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

  on(center);
}

void rotate() 
{ 
  move();
  /*
  int theDelay = 150;
   for(pos = 90; pos <= 110; pos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   headServo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(theDelay);                       // waits 15ms for the servo to reach the position 
   } 
   delay(2000);
   for(pos = 110; pos >= 90; pos -= 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   headServo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(theDelay);                       // waits 15ms for the servo to reach the position 
   } 
   */
}

void loop() {

  allOn();
  allOff();
  sendSpaghuzzinatorIsHere();
  allOff();
  delay(2000);
  strobeShortAndFast(rightYellow);
  strobeShortAndFast(rightRed);
  allOn();

  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);


  currentLookupTable = 10;  
  moveFromCenterToMax();

  delay(1000);              // wait for a second
  on(leftRed);
  off(leftYellow);
  on(rightRed);
  off(rightYellow);

  moveFromMaxToCenter();

  delay(1000);              // wait for a second
  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);

  currentLookupTable = 5;  
  moveFromCenterToMin();
  sendYouAreTerminated();
  
  allOff();
  strobeLongAndSlow(rightRed);
  allOn();
  moveFromMinToMax();
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

  moveFromMaxToMin();
  delay(1000);              // wait for a second

  moveFromMinToCenter();
  //rotate();
  off(leftRed);
  off(leftYellow);
  off(rightRed);
  off(rightYellow);
  delay(1000);              // wait for a second


  //currentLookupTable = 5;  
  //rotate();

  delay(1000);              // wait for a second
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
void moveFromMinToMax(){
  moveFwd(0, countSinusSquareLookupTableEntries);
}
void moveFromCenterToMax(){
  moveFwd(lookupTableCenter, countSinusSquareLookupTableEntries);
}
void moveFromMinToCenter(){
  moveFwd(0, lookupTableCenter);
}
void moveFromMaxToMin(){
  moveBwd(countSinusSquareLookupTableEntries, 0);
}
void moveFromCenterToMin(){
  moveBwd(lookupTableCenter, 0);
}
void moveFromMaxToCenter(){
  moveBwd(countSinusSquareLookupTableEntries, lookupTableCenter);
}
void moveFwd(int from, int to){
  for(int angleIndex = from; angleIndex < to; angleIndex++){
    moveServoTo(angle(angleIndex));
    wait();
  }
}
void moveBwd(int from, int to){
  for(int angleIndex = from-1; angleIndex >= to; angleIndex--){
    moveServoTo(angle(angleIndex));
    wait();
  }
}

/*
* This is the function that gets called periodically.
 */
void move()
{

  moveFromMinToMax();
  waitLong();
  waitLong();
  waitLong();
  waitLong();

  waitLong();
}

void moveServoTo(int angle){
  Serial.println(angle);
  headServo.write(angle); 
}

int angle(int index){
  if(currentLookupTable==5){
    return sinusSquareLookupTable90Plus5[index];
  }
  return sinusSquareLookupTable90Plus10[index];
}

void stopMove(){
  headServo.detach();
}

void setupServo(){  
  headServo.attach(headServoPin);
  headServo.write(0); 
}

void wait(){
  delay(timerInMillies);
}

void waitLong(){
  delay(5*timerInMillies);
}











