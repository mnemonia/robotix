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

  /*
  int theDelay = 15;
  for(pos = 90; pos <= 170; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    headServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
    delay(500);                       // waits 15ms for the servo to reach the position 
  for(pos = 170; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees
  {                                
    headServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
  */
  /*
  for(pos = 90; pos < 100; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    pitchServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 100; pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    pitchServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(theDelay);                       // waits 15ms for the servo to reach the position 
  } 
*/  
}

void loop() {
  
//  on(leftRed);
//  on(leftYellow);
//  on(rightRed);
//  on(rightYellow);

  on(leftRed);
  on(leftYellow);
  on(rightRed);
  on(rightYellow);
rotate();
  delay(1000);              // wait for a second
  on(leftRed);
  off(leftYellow);
  on(rightRed);
  off(rightYellow);
  delay(1000);              // wait for a second
  off(leftRed);
  on(leftYellow);
  off(rightRed);
  on(rightYellow);
  delay(1000);              // wait for a second
  on(leftRed);
  on(leftYellow);
  on(rightRed);
  on(rightYellow);
  delay(1000);              // wait for a second
  off(leftRed);
  off(leftYellow);
  off(rightRed);
  off(rightYellow);
  delay(1000);              // wait for a second
}



const int timerInMillies = 40;
const int countSinusSquareLookupTableEntries = 50;
const int sinusSquareLookupTable[] = {
65	,
65	,
65	,
65	,
66	,
66	,
67	,
68	,
69	,
71	,
73	,
75	,
77	,
78	,
80	,
82	,
84	,
86	,
87	,
88	,
89	,
89	,
90	,
90	,
90	,
90	,
90	,
90	,
90	,
91	,
91	,
92	,
93	,
94	,
96	,
98	,
100	,
102	,
103	,
105	,
107	,
109	,
111	,
112	,
113	,
114	,
114	,
115	,
115	,
115
};

/*
* This is the function that gets called periodically.
*/
void move()
{
  for(int angleIndex = 0; angleIndex < countSinusSquareLookupTableEntries; angleIndex++){
    moveServoTo(angle(angleIndex));
  //  indicateMovement();
    wait();
  }
  
  waitLong();
  for(int angleIndex = countSinusSquareLookupTableEntries-1; angleIndex >= 0; angleIndex--){
    moveServoTo(angle(angleIndex));
    wait();
  }
  
  waitLong();
}

void moveServoTo(int angle){
  Serial.println(angle);
  headServo.write(angle); 
}

int angle(int index){
  return sinusSquareLookupTable[index];
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

 








