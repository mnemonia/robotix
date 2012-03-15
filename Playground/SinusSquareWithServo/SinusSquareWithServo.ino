/* 
 * Smooth servo rotation using a sinus square function.
 * more infos: http://letsmakerobots.com/node/31697
 * created by NilsB 
 */

#include <MsTimer2.h>
#include <Servo.h> 

const int timerInMillies = 20;
const int countSinusSquareLookupTableEntries = 100;
const int sinusSquareLookupTable[] = {
	0,0,1,1,2,2,3,4,4,5,6,
	7,9,10,11,13,14,16,17,19,21,22,
	24,26,28,30,33,35,37,39,42,44,47,
	49,52,54,57,60,62,65,68,70,73,76,
	79,82,84,87,90,93,96,98,101,104,107,
	110,112,115,118,120,123,126,128,131,133,136,
	138,141,143,145,147,150,152,154,156,158,159,
	161,163,164,166,167,169,170,171,173,174,175,
	176,176,177,178,178,179,179,180,180,180,180
};
int currentValueIndex = 0;
const int movmentIndicatorPin = 13;

const Servo headServo;

void move()
{
  moveServoTo(angle());

  indicateMovement();
  
  incrementOrStop();
}

void moveServoTo(int angle){
  Serial.println(angle);
  headServo.write(angle); 
}

int angle(){
  return sinusSquareLookupTable[currentValueIndex];
}

void indicateMovement()
{
  static boolean output = HIGH;
  
  digitalWrite(movmentIndicatorPin, output);
  output = !output;
}

void incrementOrStop(){
  currentValueIndex++;
  if(currentValueIndex == countSinusSquareLookupTableEntries - 1){
    stopMove();
  }
}

void stopMove(){
  MsTimer2::stop();
  headServo.detach();
}

void setupMovementIndicator(){
  Serial.begin(9600);
  pinMode(movmentIndicatorPin, OUTPUT);
}

void setupTimer2(){
  MsTimer2::set(timerInMillies, move);
  MsTimer2::start();
}

void setupServo(){  
  headServo.attach(6);
  headServo.write(0); 
}

void setup(){
  setupMovementIndicator();
  setupServo();  
  setupTimer2();
}

void loop(){;}

