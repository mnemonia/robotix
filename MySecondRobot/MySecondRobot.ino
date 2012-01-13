#include <AFMotor.h>
#include <Servo.h> 
#include <Ultrasonic.h>

Servo radarServo;  // create servo object to control a servo 
int RADAR_PIN = 9; 
int RADAR_ATTENTION_DISTANCE_IN_CM = 60; // centimeter
int RADAR_DANGER_DISTANCE_IN_CM = 30; // centimeter
int RADAR_MOVEMENT_DELAY = 150;

const int AHEAD = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BACK = 3;
const int THREE_POINT_TURN_LEFT = 4;
const int THREE_POINT_TURN_RIGHT= 5;
int currentDirection = AHEAD;

Ultrasonic radarUltrasonic(A5,A4);
int RADAR_CENTER = 60;
int RADAR_LEFT = 0;
int RADAR_RIGHT = 120;

AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
int MOTOR_SPEED = 250;// 150;

void setup() {
  initTrace();
  initRadar();
  initMotors();
}

void loop() {
  Serial.println(currentDirection);
  
  switch(currentDirection){
    case AHEAD:{
      int ahead = lookAhead();
      if(isClear(ahead)){
        goAhead();
      }else if(isAttention(ahead)){
        stopNow();
        int left = lookLeft();
        lookAhead();
        int right = lookRight();
        if(greater(left,right)){
          currentDirection = LEFT;
        }else if(greater(right,left)){
          currentDirection = RIGHT;
        }else{
          currentDirection = BACK;
        }    
      }else if(isDanger(ahead)){
        stopNow();
        int left = lookLeft();
        lookAhead();
        int right = lookRight();
        if(greater(left,right)){
          currentDirection = THREE_POINT_TURN_LEFT;
        }else{
          currentDirection = THREE_POINT_TURN_RIGHT;
        }    
      }
      break;
    }
    case LEFT:{
      turnLeft();
      int ahead = lookAhead();
      if(isClear(ahead)){
        currentDirection = AHEAD;
      }
      break;
    }case RIGHT:{
      turnRight();
      int ahead = lookAhead();
      if(isClear(ahead)){
        currentDirection = AHEAD;
      }
      break;
    }
    case BACK:{
      backward();
      int ahead = lookAhead();
      if(isClear(ahead)){
        currentDirection = AHEAD;
      }
      break;
    }
    case THREE_POINT_TURN_LEFT:{
      backwardLeft();
      delay(2000);
      turnLeft();
      delay(1500);
      int ahead = lookAhead();
      if(isClear(ahead)){
        currentDirection = AHEAD;
      }
      break;
    }
    case THREE_POINT_TURN_RIGHT:{
      backwardRight();
      delay(2000);
      turnRight();
      delay(1500);
      int ahead = lookAhead();
      if(isClear(ahead)){
        currentDirection = AHEAD;
      }
      break;
    }
  }
}

void initTrace(){
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("My Second Robot");
}

void initRadar(){
  radarServo.attach(RADAR_PIN);  // attaches the servo on pin RADAR_INPUT_PIN to the servo object 
  radarServo.write(RADAR_CENTER);
  delay(10000);
}

void initMotors(){
  motorLeft.setSpeed(MOTOR_SPEED);     // set the speed to 200/255
  motorRight.setSpeed(MOTOR_SPEED);     // set the speed to 200/255
}

boolean isClear(int ahead){
  return ahead == 0 || ahead > RADAR_ATTENTION_DISTANCE_IN_CM;
}
boolean isAttention(int ahead){
  return ahead <= RADAR_ATTENTION_DISTANCE_IN_CM && ahead > RADAR_DANGER_DISTANCE_IN_CM;
}
boolean isDanger(int ahead){
  return ahead <= RADAR_DANGER_DISTANCE_IN_CM && ahead > 0;
}

int lookAhead(){
  moveRadarCenter();
  int center = getDistance();
  moveRadarCenterLeft();
  int centerLeft = getDistance();
  moveRadarCenterRight();
  int centerRight = getDistance();
  return centerLeft <= centerRight ? (center < centerLeft ? center : centerLeft) : (center < centerRight ? center : centerRight) ;
}

int lookLeft(){
  moveRadarLeft();
  Serial.print("Distance L: ");
//  radarServo.write(RADAR_LEFT);
//  delay(RADAR_MOVEMENT_DELAY);
  return getDistance();
}

void moveRadarCenter(){
  int pos = radarServo.read();
  if(eq(pos,RADAR_CENTER)){
    return;
  }
  if(pos > RADAR_CENTER){
    for(int i=pos; i>=RADAR_CENTER; i--){
      radarServo.write(i);
      delay(15);
    }
  }else{
    for(int i=pos; i<=RADAR_CENTER; i++){
      radarServo.write(i);
      delay(15);
    }
  }
}
void moveRadarCenterLeft(){
  for(int i=radarServo.read(); i>=RADAR_CENTER-20; i--){
    radarServo.write(i);
    delay(15);
  }
}

void moveRadarCenterRight(){
  for(int i=radarServo.read(); i<=RADAR_CENTER+20; i++){
    radarServo.write(i);
    delay(15);
  }
}

void moveRadarLeft(){
  for(int i=RADAR_CENTER; i>=RADAR_LEFT; i--){
    radarServo.write(i);
    delay(15);
  }
}
void moveRadarRight(){
  for(int i=RADAR_CENTER; i<=RADAR_RIGHT; i++){
    radarServo.write(i);
    delay(15);
  }
}

int lookRight(){
  moveRadarRight();
  Serial.print("Distance R: ");
  
//  radarServo.write(RADAR_RIGHT);
//  delay(RADAR_MOVEMENT_DELAY);
  return getDistance();
}

int getDistance(){
  long microsec = radarUltrasonic.timing();
  int distance = radarUltrasonic.convert(microsec, Ultrasonic::CM);
  return distance;
}

void goAhead(){
  Serial.println("goAhead");
  motorLeft.run(FORWARD); 
  motorRight.run(FORWARD);
}
void turnLeft(){
  Serial.println("turnLeft");
  motorLeft.run(BACKWARD); 
  motorRight.run(FORWARD);
}
void turnRight(){
  Serial.println("turnRight");
  motorLeft.run(FORWARD); 
  motorRight.run(BACKWARD);
}
void backward(){
  Serial.println("backward");
  motorLeft.run(BACKWARD); 
  motorRight.run(BACKWARD);
}
void backwardLeft(){
  Serial.println("backwardLeft");
  motorLeft.run(BACKWARD); 
  motorRight.run(RELEASE);
}
void backwardRight(){
  Serial.println("backwardRight");
  motorLeft.run(RELEASE); 
  motorRight.run(BACKWARD);
}
void stopNow(){
  Serial.println("stopNow");
  motorLeft.run(RELEASE); 
  motorRight.run(RELEASE);
}

boolean eq(int a, int b){
  int epsilon = 5;
  int diff = a - b;
  diff = diff < 0 ? (-1)*diff : diff;
  return diff <= epsilon ? true : false;
}

boolean greater(int a, int b){
  int epsilon = 5;
  double variance = a - b;
  return variance > epsilon;
}

