#include <AFMotor.h>
#include <Servo.h> 
#include <Ultrasonic.h>

typedef enum { 
  RADAR_LEFT = 0, RADAR_CENTER = 90, RADAR_RIGHT = 180 } 
RadarDirection;
Servo radarServo;  // create servo object to control a servo 
int RADAR_INPUT_PIN = 9; 
int RADAR_MOVEMENT_DELAY = 190; 
int RADAR_DISTANCE_MINIMAL_IN_CM = 50; // centimeter
int RADAR_DISTANCE_UNKNOWN_IN_CM = 0; // centimeter
Ultrasonic radarUltrasonic(A5,A4);

struct RobotState {
  int leftMotorDirection;
  int rightMotorDirection;
  int motorDelay;
};
struct RadarDistances {
  int left;
  int center;
  int right;
};

AF_DCMotor motorLeft(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
int motorSpeed = 150;
int MOTOR_DELAY = 150;
int MOTOR_TURN_DELAY = 300;

RobotState forwardState = {
  FORWARD,FORWARD,MOTOR_DELAY};
RobotState backwardState = {
  BACKWARD,BACKWARD,MOTOR_DELAY};
RobotState turnLeftState = {
  RELEASE,FORWARD,MOTOR_TURN_DELAY};
RobotState turnRightState = {
  FORWARD,RELEASE,MOTOR_TURN_DELAY};
RobotState stopState = {
  RELEASE,RELEASE,MOTOR_DELAY};
RobotState currentState = forwardState;

RadarDistances currentDistances = {
  0,0,0};
/*RadarDistances lastDistances = {
  0,0,0};
  */

void setup() {
  initTrace();
  initRadar();
  initMotors();
}

void initTrace(){
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("My First Robot");
}

void initRadar(){
  radarServo.attach(RADAR_INPUT_PIN);  // attaches the servo on pin RADAR_INPUT_PIN to the servo object 
  radarServo.write(RADAR_CENTER);
}

void initMotors(){
  motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255
}

void loop() {
  calculateRobotState();
  go();
}

void calculateRobotState(){
  measureDistanceAhead();
  if(
  currentDistances.center == RADAR_DISTANCE_UNKNOWN_IN_CM || 
  currentDistances.center >= RADAR_DISTANCE_MINIMAL_IN_CM){
    currentState = forwardState;  
    return;
  }

  measureDistanceLeft();
  measureDistanceRight();

/*  lastDistances.left = currentDistances.left;
  lastDistances.center = currentDistances.center;
  lastDistances.right = currentDistances.right;
*/
  if(eq(currentDistances.left,currentDistances.right)){
    currentState = backwardState;  
    return;
  }
  if(greater(currentDistances.left,currentDistances.right)){
    currentState = turnLeftState;  
    return;
  }
  if(greater(currentDistances.right,currentDistances.left)){
    currentState = turnRightState;  
    return;
  }
  
  currentState = stopState;
}

void go(){
  Serial.print("Go : { ");
  Serial.print(currentState.leftMotorDirection);
  Serial.print(" , ");
  Serial.print(currentState.rightMotorDirection);
  Serial.println(" }");
  motor();
  delay(150);
}

void motor(){
  motorLeft.run(currentState.leftMotorDirection); 
  motorRight.run(currentState.rightMotorDirection);
  delay(currentState.motorDelay);
}


void measureDistanceLeft(){
  moveRadarFastTo(RADAR_LEFT);
  currentDistances.left = internalMeasure();
}

void measureDistanceRight(){
  moveRadarFastTo(RADAR_RIGHT);
  currentDistances.right = internalMeasure();
}

void measureDistanceAhead(){
  moveRadarFastTo(RADAR_CENTER);
  currentDistances.center = internalMeasure();
}

int internalMeasure(){
  return radarUltrasonic.Ranging(CM);
}

void moveRadarFastTo(int radarServoPosition){
  radarServo.write(radarServoPosition);              // tell servo to go to position in variable 'pos'
  delay(RADAR_MOVEMENT_DELAY);
}

boolean eq(int a, int b){
  int epsilon = 5;
  int diff = a - b;
  diff = diff < 0 ? (-1)*diff : diff;
  return diff <= epsilon ? true : false;
}

boolean greater(int a, int b){
  return a > b;
}

