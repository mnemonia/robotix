#include <AFMotor.h>
#include <Servo.h> 
#include <Ultrasonic.h>

Servo radarServo;  // create servo object to control a servo 
int RADAR_PIN = 9; 
int RADAR_ATTENTION_DISTANCE_IN_CM = 80; // centimeter
int RADAR_DANGER_DISTANCE_IN_CM = 40; // centimeter
int RADAR_MOVEMENT_DELAY = 150;

const int AHEAD = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BACK = 3;
int currentDirection = AHEAD;

Ultrasonic radarUltrasonic(A5,A4);
int RADAR_CENTER = 90;
int RADAR_LEFT = 0;
int RADAR_RIGHT = 180;

AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
int MOTOR_SPEED = 250;// 150;

void setup() {
  initTrace();
  initRadar();
  initMotors();
}

void initTrace(){
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("My Second Robot");
}

void initRadar(){
  radarServo.attach(RADAR_PIN);  // attaches the servo on pin RADAR_INPUT_PIN to the servo object 
  radarServo.write(RADAR_CENTER);
}

void initMotors(){
  motorLeft.setSpeed(MOTOR_SPEED);     // set the speed to 200/255
  motorRight.setSpeed(MOTOR_SPEED);     // set the speed to 200/255
}

void loop() {
  int ahead = lookAhead();
  if(isClear(ahead)){
    Serial.print("Move Ahead");
    goAhead();
  }else if(isAttention(ahead)){
    turn();
  }else if(isDanger(ahead)){
    makeTreePointTurn();
  }
  delay(250);
}

void makeTreePointTurn(){
  Serial.print("makeTreePointTurn");
  stopNow();
  int left = lookLeft();
  int ahead = lookAhead();
  int right = lookRight();
  boolean turnLeft = greater(left,right);
  while(ahead != 0 && ahead < RADAR_ATTENTION_DISTANCE_IN_CM){
    Serial.print("makeTreePointTurn");
    backward();
    if(turnLeft){
      backwardLeft();
    }else{
      backwardRight();
    }
    ahead = lookAhead();
  }
  if(turnLeft){
    backwardRight();
  }else{
    backwardLeft();
  }
  delay(1000); 
 initMotors(); 
}

void turn(){
    stopNow();
    int left = lookLeft();
    int ahead = lookAhead();
    int right = lookRight();
    if(greater(left,right)){
      Serial.print("Move Left");
      turnLeft();
    }else if(greater(right,left)){
      Serial.print("Move Right");
      turnRight();
    }else{
      Serial.print("Move Back");
      backward();
      delay(2000);
      uturn();
    }    
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
  Serial.print("Distance A: ");
//  radarServo.write(RADAR_CENTER);
//  delay(RADAR_MOVEMENT_DELAY);
  return getDistance();
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

void moveRadarLeft(){
  for(int i=RADAR_CENTER; i>=0; i--){
    radarServo.write(i);
    delay(15);
  }
}
void moveRadarRight(){
  for(int i=RADAR_CENTER; i<=180; i++){
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
  Serial.println(distance);
  return distance;
}

void goAhead(){
  motorLeft.run(FORWARD); 
  motorRight.run(FORWARD);
}
void turnLeft(){
  motorLeft.run(BACKWARD); 
  motorRight.run(FORWARD);
}
void turnRight(){
  motorLeft.run(FORWARD); 
  motorRight.run(BACKWARD);
}
void backward(){
  motorLeft.run(BACKWARD); 
  motorRight.run(BACKWARD);
}
void backwardLeft(){
  motorRight.setSpeed(255);     // set the speed to 200/255
  motorLeft.run(BACKWARD); 
  motorRight.run(BACKWARD);
}
void backwardRight(){
  motorLeft.setSpeed(255);     // set the speed to 200/255
  motorLeft.run(BACKWARD); 
  motorRight.run(BACKWARD);
}
void stopNow(){
  motorLeft.run(RELEASE); 
  motorRight.run(RELEASE);
  delay(150);
}

void uturn(){
  turnRight(); 
  turnRight();
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

