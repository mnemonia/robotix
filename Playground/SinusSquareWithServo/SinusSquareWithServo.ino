#include <MsTimer2.h>
#include <Servo.h> 

int sinusSquareLookupTable[] = {
  1,
4,
10,
17,
26,
37,
49,
62,
76,
90,
104,
118,
131,
143,
154,
163,
170,
176,
179,
180};

int steps = 20;

const int led_pin = 13;			// default to pin 13

Servo headServo;  // create servo object to control a servo 

void flash()
{
  static boolean output = HIGH;
  
  digitalWrite(led_pin, output);
  output = !output;
}

void setup(){
  Serial.begin(9600);

  pinMode(led_pin, OUTPUT);

  MsTimer2::set(1000/20, timerIsr); // 500ms period
  MsTimer2::start();

  headServo.attach(6);
  toZero();
}

void loop(){
}

/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
int angleMemento = 0;
int currentValueIndex = 0;
void timerIsr()
{
  if(steps==currentValueIndex){
    currentValueIndex = 0;
  }
  int angle = sinusSquareLookupTable[currentValueIndex];
  Serial.println(angle);
  headServo.write(angle); 
  currentValueIndex++;
  angleMemento = angle;

  digitalWrite( 13, digitalRead(13) ^ 1 );
}

int calcRotationDuration(int angle){
  if(angle > angleMemento){
    return 10 * (angle - angleMemento);
  }else if(angle < angleMemento){
    return 10 * (angleMemento - angle);
  }
  return 10;
}
void toZero(){  
 // headServo.write(0);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}

