// motor A
int motorPinA1 = 13;
int motorPinA2 = 12;
int speedPinA = 10;
// motor B
// motor A
int steeringPinB1 = 11;
int steeringPinB2 = 8;
int speedPinB = 9;
unsigned long time;
int speed;
int dir;
void setup() {
  pinMode(motorPinA1, OUTPUT);
  pinMode(motorPinA2, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(steeringPinB1, OUTPUT);
  pinMode(steeringPinB2, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  speed = 200;
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);
}
void motorFwd(){
  digitalWrite(motorPinA1, HIGH);
  digitalWrite(motorPinA2, LOW);
}
void motorStop(){
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, LOW);
}
void motorBwd(){
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, HIGH);
}

void steeringLeft(){
  digitalWrite(steeringPinB1, HIGH);
  digitalWrite(steeringPinB2, LOW);
}
void steeringNeutral(){
  digitalWrite(steeringPinB1, LOW);
  digitalWrite(steeringPinB2, LOW);
}
void steeringRight(){
  digitalWrite(steeringPinB1, LOW);
  digitalWrite(steeringPinB2, HIGH);
}
void wait(){
 delay(4000);
 }
void loop() {
  motorFwd();
  wait();
  motorStop();
  wait();
  motorBwd();
  wait();
  motorStop();
  wait();
  
  steeringLeft();
  wait();
  steeringNeutral();
  wait();
  steeringRight();  
  wait();
  steeringNeutral();

  wait();
  wait();
}

