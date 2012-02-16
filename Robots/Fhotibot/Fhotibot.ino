extern "C"{
  #include "sTheUnit.h"
}

#include <AFMotor.h>
#include <Servo.h> 
#include <DistanceGP2Y0A21YK.h>

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN      PIND
#define IRpin          2

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "ircodes.h"

DistanceGP2Y0A21YK proxSensorLeft;
DistanceGP2Y0A21YK proxSensorRight;
int distance;
unsigned char distanceState;
 
//Servo traceServo;  // create servo object to control a servo 
//Servo headServo;  // create servo object to control a servo 

const int proxSensorLeftPin = A5; //analog pin 5
const int proxSensorRightPin = A4; //analog pin 4

AF_DCMotor motorLeft(1/*, MOTOR12_64KHZ*/); // create motor #2, 64KHz pwm
AF_DCMotor motorRight(2); // create motor #2, 64KHz pwm
const int motorSpeed = 200;

void setup(){
  Serial.begin(9600);

  motorLeft.setSpeed(motorSpeed);     // set the speed to 200/255
  motorRight.setSpeed(motorSpeed);     // set the speed to 200/255

  proxSensorLeft.begin(proxSensorLeftPin);
  proxSensorRight.begin(proxSensorRightPin);
  
  distanceState = C8_Clear;
//  traceServo.attach(9);
//  headServo.attach(10);

  if(!fINIT_()){
  // Fehler in fININT ...
  }

}

void loop(){
  feedDrive();
  feedFinder();

  delay(20);
}

void feedDrive(){
  distance = proxSensorLeft.getDistanceCentimeter();
  int distanceRight = proxSensorRight.getDistanceCentimeter();
  distance = distance > distanceRight ? distanceRight : distance;

  if(distance>19){
    radar(C8_Clear);
  }else if(distance<=19 && distance>9){
    radar(C8_Attention);
  }else{
    radar(C8_Danger);
  }
}

void feedFinder(){
  int numberpulses;
  
  numberpulses = listenForIR();
  
  Serial.print("Heard ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");
  if (IRcompare(numberpulses, IRsignal_Key1)) {
    Serial.println("Left");
    IN_.Direction(C10_Left);
  }
  if (IRcompare(numberpulses, IRsignal_Key3)) {
    Serial.println("Right");
    IN_.Direction(C10_Right);
  }
    if (IRcompare(numberpulses, IRsignal_Key2)) {
    Serial.println("Ahead");
      IN_.Direction(C10_Ahead);
  }
    if (IRcompare(numberpulses, IRsignal_Key5)) {
    Serial.println("Behind");
      IN_.Direction(C10_Behind);
  }
}

void radar(unsigned char name_AutonomousDriveEvent){
  if(distanceState==name_AutonomousDriveEvent){
      return;
  }
  
  distanceState = name_AutonomousDriveEvent;
  Serial.println(name_AutonomousDriveEvent);
  
  //uCHAN_AutonomousDriveEvents(name_AutonomousDriveEvent);
    IN_.AutonomousDriveEvents(name_AutonomousDriveEvent);
  TRG_.CHAIN_();  
}

extern "C"
{

/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_AutonomousDriveEvents (unsigned char name_)
{
  IN_.AutonomousDriveEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_ObstacleEvents (unsigned char name_)
{
  IN_.ObstacleEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_RemoteControlEvents (unsigned char name_)
{
  IN_.RemoteControlEvents(name_);
  TRG_.CHAIN_();  
}

void uCHAN_LeftMotor (unsigned char name_)
{
 	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_Backward:
          Serial.println("Left BACKWARD");
          motorLeft.run(BACKWARD);
  	  break;
	case C4_Forward:
          Serial.println("Left FORWARD");
          motorLeft.run(FORWARD);
          break;
	case C4_Stop:
          Serial.println("Left RELEASE");
          motorLeft.run(RELEASE);
          break;
	default: 
		break;
	}
}

void uCHAN_RightMotor (unsigned char name_)
{
  	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_Backward:
          Serial.println("Right BACKWARD");
          motorRight.run(BACKWARD);
          break;
	case C5_Forward:
          Serial.println("Right FORWARD");
          motorRight.run(FORWARD);
          break;
	case C5_Stop:
          Serial.println("Right RELEASE");
          motorRight.run(RELEASE);
          break;
	default: 
		break;
	}
}

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.AutonomousDriveEvents = uCHAN_AutonomousDriveEvents;
	OUT_.LeftMotor = uCHAN_LeftMotor;
	OUT_.ObstacleEvents = uCHAN_ObstacleEvents;
	OUT_.RemoteControlEvents = uCHAN_RemoteControlEvents;
	OUT_.RightMotor = uCHAN_RightMotor;
}

}

boolean IRcompare(int numpulses, int Signal[]) {
  
  for (int i=0; i< numpulses-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    
    /*
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
    */
    
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
    
    /*
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
    */
    
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
    
    //Serial.println();
  }
  // Everything matched!
  return true;
}

int listenForIR(void) {
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
  
//  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH

       // count off another few microseconds
       highpulse++;
       delayMicroseconds(RESOLUTION);

       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
  
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
       delayMicroseconds(RESOLUTION);
       if ((lowpulse >= MAXPULSE)  && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
  }
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
  
  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");
}

