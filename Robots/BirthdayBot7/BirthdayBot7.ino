#include <Servo.h>

const int timerInMillies = 10;
/*
const int countSinusSquareLookupTableEntries = 181;
const int sinusSquareLookupTable[] = {
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,1,1,1,1,
1,1,2,2,2,2,3,3,3,
4,4,5,5,6,6,7,7,8,
9,9,10,11,12,13,14,14,15,
16,17,18,20,21,22,23,24,25,
27,28,29,31,32,34,35,37,38,
40,41,43,45,46,48,50,52,53,
55,57,59,61,63,64,66,68,70,
72,74,76,78,80,82,84,86,88,
90,92,94,96,98,100,102,104,106,
108,110,112,114,116,117,119,121,123,
125,127,128,130,132,134,135,137,139,
140,142,143,145,146,148,149,151,152,
153,155,156,157,158,159,160,162,163,
164,165,166,166,167,168,169,170,171,
171,172,173,173,174,174,175,175,176,
176,177,177,177,178,178,178,178,179,
179,179,179,179,179,180,180,180,180,
180,180,180,180,180,180,180,180,180,
180
};
*/
/*
const int countSinusSquareLookupTableEntries = 80;
const int sinusSquareLookupTable[] = 
{
20, 20, 20, 20, 20, 20, 20, 20, 21, 21,
21, 22, 22, 23, 23, 24, 25, 26, 27, 28,
29, 30, 32, 33, 35, 37, 38, 40, 42, 44,
46, 48, 51, 53, 55, 58, 60, 63, 65, 68,
70, 72, 75, 77, 80, 82, 85, 87, 89, 92,
94, 96, 98, 100, 102, 103, 105, 107, 108, 110,
111, 112, 113, 114, 115, 116, 117, 117, 118, 118,
119, 119, 119, 120, 120, 120, 120, 120, 120, 120
};
*/
const int countSinusSquareLookupTableEntries = 67 * 10;
const int sinusSquareLookupTable[] = 
{
20, 20, 20, 21, 21, 21, 21, 21, 21, 21,
21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
21, 21, 21, 21, 21, 21, 22, 22, 22, 22,
22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
22, 22, 22, 22, 22, 22, 23, 23, 23, 23,
23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
23, 23, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 24, 25, 25, 25, 25, 25,
25, 25, 25, 25, 25, 25, 25, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 27, 27, 27,
27, 27, 27, 27, 27, 27, 28, 28, 28, 28,
28, 28, 28, 28, 28, 29, 29, 29, 29, 29,
29, 29, 29, 30, 30, 30, 30, 30, 30, 30,
31, 31, 31, 31, 31, 31, 31, 31, 32, 32,
32, 32, 32, 32, 33, 33, 33, 33, 33, 33,
33, 34, 34, 34, 34, 34, 34, 35, 35, 35,
35, 35, 35, 36, 36, 36, 36, 36, 36, 37,
37, 37, 37, 37, 37, 38, 38, 38, 38, 38,
39, 39, 39, 39, 39, 39, 40, 40, 40, 40,
40, 41, 41, 41, 41, 41, 42, 42, 42, 42,
42, 43, 43, 43, 43, 43, 44, 44, 44, 44,
44, 45, 45, 45, 45, 45, 46, 46, 46, 46,
46, 47, 47, 47, 47, 48, 48, 48, 48, 48,
49, 49, 49, 49, 50, 50, 50, 50, 50, 51,
51, 51, 51, 52, 52, 52, 52, 52, 53, 53,
53, 53, 54, 54, 54, 54, 55, 55, 55, 55,
56, 56, 56, 56, 56, 57, 57, 57, 57, 58,
58, 58, 58, 59, 59, 59, 59, 60, 60, 60,
60, 61, 61, 61, 61, 62, 62, 62, 62, 63,
63, 63, 63, 64, 64, 64, 64, 65, 65, 65,
65, 66, 66, 66, 66, 67, 67, 67, 67, 68,
68, 68, 68, 69, 69, 69, 69, 70, 70, 70,
70, 70, 71, 71, 71, 71, 72, 72, 72, 72,
73, 73, 73, 73, 74, 74, 74, 74, 75, 75,
75, 75, 76, 76, 76, 76, 77, 77, 77, 77,
78, 78, 78, 78, 79, 79, 79, 79, 80, 80,
80, 80, 81, 81, 81, 81, 82, 82, 82, 82,
83, 83, 83, 83, 84, 84, 84, 84, 84, 85,
85, 85, 85, 86, 86, 86, 86, 87, 87, 87,
87, 88, 88, 88, 88, 88, 89, 89, 89, 89,
90, 90, 90, 90, 90, 91, 91, 91, 91, 92,
92, 92, 92, 92, 93, 93, 93, 93, 94, 94,
94, 94, 94, 95, 95, 95, 95, 95, 96, 96,
96, 96, 96, 97, 97, 97, 97, 97, 98, 98,
98, 98, 98, 99, 99, 99, 99, 99, 100, 100,
100, 100, 100, 101, 101, 101, 101, 101, 101, 102,
102, 102, 102, 102, 103, 103, 103, 103, 103, 103,
104, 104, 104, 104, 104, 104, 105, 105, 105, 105,
105, 105, 106, 106, 106, 106, 106, 106, 107, 107,
107, 107, 107, 107, 107, 108, 108, 108, 108, 108,
108, 109, 109, 109, 109, 109, 109, 109, 109, 110,
110, 110, 110, 110, 110, 110, 111, 111, 111, 111,
111, 111, 111, 111, 112, 112, 112, 112, 112, 112,
112, 112, 112, 113, 113, 113, 113, 113, 113, 113,
113, 113, 114, 114, 114, 114, 114, 114, 114, 114,
114, 114, 115, 115, 115, 115, 115, 115, 115, 115,
115, 115, 115, 115, 116, 116, 116, 116, 116, 116,
116, 116, 116, 116, 116, 116, 116, 117, 117, 117,
117, 117, 117, 117, 117, 117, 117, 117, 117, 117,
117, 117, 117, 118, 118, 118, 118, 118, 118, 118,
118, 118, 118, 118, 118, 118, 118, 118, 118, 118,
118, 118, 118, 119, 119, 119, 119, 119, 119, 119,
119, 119, 119, 119, 119, 119, 119, 119, 119, 119,
119, 119, 119, 119, 119, 119, 119, 119, 119, 119,
119, 119, 119, 119, 119, 119, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
};

const int movmentIndicatorPin = 12;

Servo headServo;

// these constants won't change:
const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A1; // the piezo is connected to analog pin 0
const int knockTreshold = 40;  // threshold value to decide when the detected sound is a knock or not
int previousKnockInMillies = 0;
long knockInterval = 1000;           // interval at which to blink (milliseconds)


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ambientSensorValue = 0;
int ambientSensorPin = A0;
int angleIndex = countSinusSquareLookupTableEntries / 2;

int pos = 20;    // variable to store the servo position 
boolean isTurnClockwise = false;
boolean isOff = true;

void setup() {
  Serial.begin(9600);       // use the serial port
  setupMovementIndicator();
  setupEyes();
  setupServo();    
}

void setupEyes(){
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  eyesOn();
  delay(400);
  eyesOff();
  delay(50);
  eyesOn();
  delay(400);
  eyesOff();
  delay(50);
  eyesOn();
  delay(200);
  eyesOff();
}

void eyesOn(){
  digitalWrite(ledPin, HIGH);
}
void eyesOff(){
  digitalWrite(ledPin, LOW);
}

void checkAndSetOnOff(){
  int value = analogRead(knockSensor);
  Serial.print(value);
  Serial.print(" : ");
  Serial.println(knockTreshold);

  unsigned long currentMillis = millis();

  if(value >= knockTreshold && currentMillis - previousKnockInMillies > knockInterval) {
    // save the last time you blinked the LED 
    previousKnockInMillies = currentMillis;   

    isOff = !isOff;
    Serial.println(isOff);
  }
}

void checkAmbientLight(){
  // read the value from the sensor:
  ambientSensorValue = analogRead(ambientSensorPin);    
  //  Serial.println(ambientSensorValue);
  if(ambientSensorValue < 50){
    // turn the ledPin on
    eyesOn();
  }
  else{
    if(isOff){
      eyesOff();
    }
  }
}
void moveHead(){
    headServo.attach(9);  // attaches the servo on pin 9 to the servo object 
    if(isTurnClockwise){
      for(; angleIndex < countSinusSquareLookupTableEntries; angleIndex++){
        moveServoTo(angle(angleIndex));
        checkAndSetOnOff();
        if(isOff){
    eyesOff();
          return;
        } 
        checkAmbientLight();      
        indicateMovement();
        wait();
      }     
     angleIndex =  countSinusSquareLookupTableEntries - 1;
/*      for(pos = pos; pos>=20; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
       checkAndSetOnOff();
        if(isOff){
          return;
        } 
        checkAmbientLight();      
        delay(15);                       // waits 15ms for the servo to reach the position 
      } 
      */
      isTurnClockwise = false;
    }else{
      for(; angleIndex >= 0; angleIndex--){
        moveServoTo(angle(angleIndex));
        indicateMovement();
        checkAndSetOnOff();
        if(isOff){
          return;
        } 
        checkAmbientLight();   
        wait();
      }
      angleIndex = 0;
      /*
      for(pos = pos; pos < 150; pos += 1)  // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        checkAndSetOnOff();
        if(isOff){
          return;
        } 
        checkAmbientLight();   
  
        delay(15);                       // waits 15ms for the servo to reach the position 
      } 
      */
      isTurnClockwise = true;
    }
    headServo.detach();
}
void loop() {
  checkAmbientLight();
  
  checkAndSetOnOff();
  if(isOff){
    eyesOff();
    return;
  }  

  if(!isOff){
    eyesOn();
  }
  moveHead();
  if(isOff){
    eyesOff();
  }
  delay(20);  // delay to avoid overloading the serial port buffer
}

void moveServoTo(int angle){
  Serial.println(angle);
  headServo.write(angle); 
}

int angle(int index){
  return sinusSquareLookupTable[index];
}

void indicateMovement()
{
  static boolean output = HIGH;
  
  digitalWrite(movmentIndicatorPin, output);
  output = !output;
}

void stopMove(){
  headServo.detach();
}

void setupMovementIndicator(){
  Serial.begin(9600);
  pinMode(movmentIndicatorPin, OUTPUT);
}

void setupServo(){  
  headServo.attach(9);
  headServo.write(90); 
  headServo.detach();
}

void wait(){
  delay(timerInMillies);
}

void waitLong(){
  delay(5*timerInMillies);
}

