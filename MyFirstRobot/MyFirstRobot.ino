#include <Servo.h> 
#include <Ultrasonic.h>
#include <AFMotor.h>

int TRACE = 0;
typedef enum { RADAR_LEFT_TO_RIGHT, RADAR_RIGHT_TO_LEFT } RADAR_MOVING_DIRECTION ;
typedef enum { RADAR_LEFT = 0, RADAR_CENTER = 90, RADAR_RIGHT = 180 } RADAR_POSITION;
typedef enum { MOVE_TO_LEFT, MOVE_STRAIGHT_ABHEAD, MOVE_TO_RIGHT, MOVE_BACKWARDS } DIRECTION_TO_MOVE;

Servo radarServo;  // create servo object to control a servo 
RADAR_MOVING_DIRECTION radarServoMovingDirection = RADAR_LEFT_TO_RIGHT; 
int RADAR_MOVEMENT_DELAY = 190; 
int RADAR_DISTANCES[] = { 0, 0, 0 };
int RADAR_DISTANCES_COUNT = 3;
int RADAR_DISTANCE_TO_CHANGE_MOVING_DIRECTION_IN_CM = 50; // centimeter
Ultrasonic radarUltrasonic(A5,A4);
int currentMoveToDirection = MOVE_STRAIGHT_ABHEAD;

AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int motorSpeed = 150;
int MOTOR_TURN_MOVEMENT_DELAY = 500; 

void setup() 
{ 
  initTrace();
  initRadar();
  initMotors();
} 

void initMotors(){
  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255
  motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
}


void motorForward(){
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD); 
}

void motorBackward(){
  motorRight.run(BACKWARD); 
  motorLeft.run(BACKWARD);
}

void motorTurnRight(){
  motorRight.run(RELEASE); 
  motorLeft.run(FORWARD); 
  delay(MOTOR_TURN_MOVEMENT_DELAY);
}

void motorTurnLeft(){
  motorRight.run(FORWARD); 
  motorLeft.run(RELEASE); 
  delay(MOTOR_TURN_MOVEMENT_DELAY);
}

void moveMotors(int moveToDirection){
  switch(moveToDirection){
    case MOVE_STRAIGHT_ABHEAD:
      motorForward();
      break;
    case MOVE_TO_LEFT:
      motorTurnLeft();
      break;
    case MOVE_TO_RIGHT:
      motorTurnRight();
      break;
    case MOVE_BACKWARDS:{
      motorBackward();
      break;
    }
    default:
        Serial.print("Error in moveMotors");
  }
}
void loop() 
{ 
  moveRadar();
  int moveToDirection = findDirectionToMove();
  //if(moveToDirection!=currentMoveToDirection){
    currentMoveToDirection = moveToDirection;
    moveMotors(moveToDirection);
    Serial.print("Moving to: ");
    Serial.println(moveToDirection);
  //}
  delay(400);
} 

void initRadar(){
  radarServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  radarServo.write(0);
  radarServoMovingDirection = RADAR_LEFT_TO_RIGHT;
}

int findDirectionToMove(){
  if(RADAR_DISTANCES[1] >= RADAR_DISTANCE_TO_CHANGE_MOVING_DIRECTION_IN_CM){
    return MOVE_STRAIGHT_ABHEAD;
  }
  
  if(RADAR_DISTANCES[0] > RADAR_DISTANCES[2]){
    return MOVE_TO_LEFT;
  }
  if(RADAR_DISTANCES[2] > RADAR_DISTANCES[0]){
    return MOVE_TO_RIGHT;
  }

  return MOVE_BACKWARDS;
}

void moveRadar(){
  moveRadarTo(90);
  delay(RADAR_MOVEMENT_DELAY);
  RADAR_DISTANCES[1] = measureDistance();
  if(RADAR_DISTANCES[1]>RADAR_DISTANCE_TO_CHANGE_MOVING_DIRECTION_IN_CM){
    return;
  }  
  
  moveRadarTo(0);
  delay(RADAR_MOVEMENT_DELAY);
  RADAR_DISTANCES[0] = measureDistance();

  moveRadarTo(90);
  delay(RADAR_MOVEMENT_DELAY);
  RADAR_DISTANCES[1] = measureDistance();

  moveRadarTo(180);
  delay(RADAR_MOVEMENT_DELAY);
  RADAR_DISTANCES[2] = measureDistance();

  moveRadarTo(90);
  
  Serial.print("Distances: ");
  Serial.print(RADAR_DISTANCES[0]);  
  Serial.print("cm left, ");
  Serial.print(RADAR_DISTANCES[1]);  
  Serial.print("cm ahead, ");
  Serial.print(RADAR_DISTANCES[2]);  
  Serial.println("cm right");
}

void moveRadarTo(int radarServoPosition){
    moveRadarFastTo(radarServoPosition);
}

void moveRadarSlowTo(int radarServoPosition){
  int currentRadarServoPosition = radarServo.read();
  if(currentRadarServoPosition>radarServoPosition){
    for(int pos = currentRadarServoPosition; pos>=radarServoPosition; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      radarServo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }   
  }else if(currentRadarServoPosition<radarServoPosition){
    for(int pos = currentRadarServoPosition; pos <= radarServoPosition; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      radarServo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }
}

void moveRadarFastTo(int radarServoPosition){
    radarServo.write(radarServoPosition);              // tell servo to go to position in variable 'pos' 
}

int measureDistance(){
  return radarUltrasonic.Ranging(CM);
}

void initTrace(){
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Dragon Bot 1");
}
