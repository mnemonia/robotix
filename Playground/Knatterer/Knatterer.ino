/*
 * HCSR04Ultrasonic/examples/UltrasonicDemo/UltrasonicDemo.pde
 *
 * SVN Keywords
 * ----------------------------------
 * $Author: cnobile $
 * $Date: 2011-09-17 02:43:12 -0400 (Sat, 17 Sep 2011) $
 * $Revision: 29 $
 * ----------------------------------
 */

#include <Ultrasonic.h>
#include <Servo.h> 
#include <AFMotor.h>

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

//#define TRIGGER_PIN  12
#define TRIGGER_PIN  A0
//#define ECHO_PIN     13
#define ECHO_PIN     A1
#define SERVO_PIN     10

Servo radarServo;  // create servo object to control a servo 
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
AF_DCMotor motorRight(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
int motorSpeed = 200;
int ledPin =  A3;      // the number of the LED pin

void setup()
  {
  Serial.begin(9600);
  initRadar();
  initMotors();
    pinMode(ledPin, OUTPUT); 
  }

void loop()
  {
    digitalWrite(ledPin, HIGH);
 forward();
  delay(2000);
    digitalWrite(ledPin, LOW);
  turn();
  delay(500);
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();


  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  int pauseBetweenNotes = cmMsec * 1.30;
  tone(A2, NOTE_C4,1000);
//  delay(pauseBetweenNotes);
  noTone(A2);
 /* 
  tone(A2, NOTE_G3,cmMsec);
  delay(pauseBetweenNotes);
  noTone(A2);
  tone(A2, NOTE_A3,cmMsec);
  delay(pauseBetweenNotes);
  noTone(A2);
  tone(A2, NOTE_G3,cmMsec);
  delay(pauseBetweenNotes);
  noTone(A2);
  tone(A2, NOTE_B3,cmMsec);
  delay(pauseBetweenNotes);
  noTone(A2);
  tone(A2, NOTE_C4,cmMsec);
  delay(pauseBetweenNotes);
  noTone(A2);

  Serial.print("MS: ");
  Serial.print(microsec);
  Serial.print(", CM: ");
  Serial.println(cmMsec);
  */
  //motorRight.run(RELEASE);

  radarServo.write(90);
  delay(1000);
  radarServo.write(0);

  }
  
 void initRadar(){
  radarServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
  radarServo.write(0);
}

void initMotors(){
  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255
  //motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
}

void forward(){
  motorRight.run(FORWARD);      // turn it on going forward
 //motor2.run(FORWARD);      // turn it on going forward
}

void turn(){
  motorRight.run(RELEASE);      // turn it on going forward
  //motor2.run(FORWARD);      // turn it on going forward
}
