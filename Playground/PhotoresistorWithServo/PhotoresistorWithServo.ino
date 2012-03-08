// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

/* MESSAGE Enumeration of CHANNEL PositionInfo */
#define C1_ 0
#define C1_Ahead 1
#define C1_Left 2
#define C1_Right 3
#define C1_Unknown 4

Servo myservo;  // create servo object to control a servo 
 
int potpinLeft = A0;  // analog pin used to connect the potentiometer
int potpinRight = A1;  // analog pin used to connect the potentiometer
int valLeft;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object 
  pinMode(9, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);  
} 
 
void loop() 
{ 
  finder();
  delay(15);                           // waits for the servo to get there 
} 
boolean finder(){
  int targetDirection = selectTargetDirection(
                          analogRead(A0), 
                          analogRead(A1));
  //if(targetDirection == currentTargetDirectionMemento){
  //  return false;
  //}
  
  Serial.println(targetDirection);
  
  off(9);
  off(12);
  off(13);  
  
  switch(targetDirection){
    case C1_Ahead:
      on(9);
      break;
    case C1_Left:
      on(13);
      break;
    case C1_Right:
      on(12);
      break;
    case C1_Unknown:
      //on(9);
      break;
  }

  //IN_.PositionInfo(targetDirection);
  
  //currentTargetDirectionMemento = targetDirection;
  return true;
}

int selectTargetDirection(int valLeft, int valRight){
  if(eq(valLeft,valRight)){
    return C1_Ahead;
  }
  
  if(valLeft < valRight){
    return C1_Left;
  }

  return C1_Right;
}
void off(int pin){
  digitalWrite(pin, LOW);
}
void on(int pin){
  digitalWrite(pin, HIGH);
}
boolean eq(int a, int b){
  return ( abs(a - b) < 20 ) ;
}
