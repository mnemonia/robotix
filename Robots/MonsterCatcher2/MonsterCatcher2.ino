#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


#include <Ultrasonic.h>

Ultrasonic ultrasonic(7,6);

#include <SoftwareServo.h>
SoftwareServo servo;
int servoPin = 5;

int bumperPin = 2;

boolean isFindingBed = false;

long prevDrunkDriveMillis = 0;
long drunkDriveInterval = 500;           // interval at which to blink (milliseconds)

boolean isDrunkDrive = false;

////MOTORs/////////////////////////////////////
const int C1_BACKWARD = 0;
const int C1_BWD_LEFT = 1;
const int C1_BWD_RIGHT = 2;
const int C1_FORWARD = 3;
const int C1_LEFT = 4;
const int C1_RIGHT = 5;
const int C1_FWD_LEFT = 6;
const int C1_FWD_RIGHT = 7;
// motor A
int dir1PinA = 13;
int dir2PinA = 12;
int speedPinA = 10;
// motor B
// motor A
int dir1PinB = 11;
int dir2PinB = 8;
int speedPinB = 9;
int speed = 200;
///Drive
int currentDirection = C1_FORWARD;
///////////////////////////////////////////

int tonePin = 3;
int noteDuration = 1000;

void setup(){
  Serial.begin(9600);
  initBumper();
  initMotors();
  initServo();
}

void loop(){
  if(isBumped()){
    bumpBehavior();
  }else{
    if(isUnderBed()){
      stopFindingBed();
      drunkDrive();
    }else{
      stopDrunkDrive();
      findBed();
    }
  }
  
  tick();
}

void initServo(){
  servo.attach(servoPin); 
  servo.setMaximumPulse(2200);
  //servo.write(servoPos);
  servo.write(90);                  
}

void stopDrunkDrive(){
  isDrunkDrive = false;
}

void stopFindingBed(){
  isFindingBed = false;
}

void initMotors(){
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  speed = 200;
  
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);
}


void tick(){
  incDrunkDriveTime();
}

void incDrunkDriveTime(){
  unsigned long currentMillis = millis();

  if(currentMillis - prevDrunkDriveMillis > drunkDriveInterval) {
    prevDrunkDriveMillis = currentMillis;   
  }
}

void findBed(){
  Serial.println("Looking for a bed...");
  if(!isFindingBed){
    isFindingBed = true;
    tone(tonePin, NOTE_C1, 2 * noteDuration);
    driveChannel(C1_LEFT);
    delay(4000);
    tone(tonePin, NOTE_C4, noteDuration);
    driveChannel(C1_FORWARD);
    noTone(tonePin);
  }
}

void drunkDrive(){
  Serial.println("Drunk-Drive on");
  isDrunkDrive = true;
  tone(tonePin, NOTE_A2, 2 * noteDuration);
  driveChannel(C1_FWD_LEFT);
  servo.write(60);
  SoftwareServo::refresh();

  tone(tonePin, NOTE_A3, noteDuration);
  delay(500);
  tone(tonePin, NOTE_C3, noteDuration);
  delay(500);
  tone(tonePin, NOTE_D3, noteDuration);
  delay(500);
  tone(tonePin, NOTE_E4, noteDuration);
  delay(500);
  driveChannel(C1_FWD_RIGHT);    
  servo.write(180);
  SoftwareServo::refresh();
  
  tone(tonePin, NOTE_A4, noteDuration);
  delay(2000);
  servo.write(60);
  SoftwareServo::refresh();

  noTone(tonePin);
}

void bumpBehavior(){
  Serial.println("Object-Avoidance on");
  tone(tonePin, NOTE_E1, 3*noteDuration);
  driveChannel(C1_BACKWARD);
  delay(3000);
  tone(tonePin, NOTE_E3, 2*noteDuration);
  driveChannel(C1_LEFT);    
  delay(3000);
  driveChannel(C1_FORWARD);
  noTone(tonePin);  
}

boolean isUnderBed(){
  int distance = ultrasonic.Ranging(CM);
  boolean isBedAbove = distance > 0 && distance < 90;
  Serial.print("Bed is above: ");
  Serial.print(isBedAbove ? "yes, " : "no, ");
  Serial.println(distance);
  return isBedAbove;
}

void initBumper(){
  pinMode(bumperPin, INPUT);
  digitalWrite(bumperPin,HIGH);
}

boolean isBumped(){
  boolean isBumped = digitalRead(bumperPin)==LOW;
  Serial.print("Bumped: ");
  Serial.println(isBumped ? "yes" : "no");
  return isBumped;
}

void driveChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C1_BACKWARD:
              Serial.println("DRIVE BACKWARD");
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_BWD_LEFT:
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_BWD_RIGHT:
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_FORWARD:
              Serial.println("DRIVE FORWARD");

                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
                
		break;
	case C1_LEFT:
              Serial.println("DRIVE LEFT");
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, HIGH);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_RIGHT:
              Serial.println("DRIVE RIGHT");
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, HIGH);
		break;
	case C1_FWD_LEFT:
                digitalWrite(dir1PinA, LOW);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, HIGH);
                digitalWrite(dir2PinB, LOW);
		break;
	case C1_FWD_RIGHT:
                digitalWrite(dir1PinA, HIGH);
                digitalWrite(dir2PinA, LOW);
                digitalWrite(dir1PinB, LOW);
                digitalWrite(dir2PinB, LOW);
		break;
	default: 
		break;
	}
}

