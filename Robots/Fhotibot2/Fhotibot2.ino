/* Raw IR commander
 
 This sketch/program uses the Arduno and a PNA4602 to 
 decode IR received.  It then attempts to match it to a previously
 recorded IR signal
 
 Code is public domain, check out www.ladyada.net and adafruit.com
 for more tutorials! 
 */

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN      PIND
#define IRpin          2
#define BUMPER_PIN     8


#define MOTOR_SIMULATION_LEFT_FWD 6
#define MOTOR_SIMULATION_LEFT_STOP 5
#define MOTOR_SIMULATION_LEFT_BWD 7

#define MOTOR_SIMULATION_RIGHT_FWD 11
#define MOTOR_SIMULATION_RIGHT_STOP 10
#define MOTOR_SIMULATION_RIGHT_BWD 12

// the maximum pulse 65000 we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 4178

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

extern "C"{
#include "sTheUnit.h"
}
#include "ircodesSilverlitPicooZ2006.h"
#include <AFMotor.h>

#include <Ultrasonic.h>
#define TRIGGER_PIN  4
#define ECHO_PIN     13

Ultrasonic ultrasonic(TRIGGER_PIN,ECHO_PIN);

//AF_DCMotor motorLeft(1);
//AF_DCMotor motorRight(2);

int theSpeed = 200;
unsigned char lastEvent = C1_;
int currentMillies = 0;

const int ledPin =  12;      // the number of the LED pin

int currentTargetDirectionMemento = C1_;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
  //  motorLeft.setSpeed(theSpeed);     // set the speed to 200/255
  //  motorRight.setSpeed(theSpeed);     // set the speed to 200/255

  pinMode(BUMPER_PIN, INPUT);     
  pinMode(MOTOR_SIMULATION_LEFT_FWD, OUTPUT);     
  pinMode(MOTOR_SIMULATION_LEFT_STOP, OUTPUT);     
  pinMode(MOTOR_SIMULATION_LEFT_BWD, OUTPUT);     
  pinMode(MOTOR_SIMULATION_RIGHT_FWD, OUTPUT);     
  pinMode(MOTOR_SIMULATION_RIGHT_STOP, OUTPUT);     
  pinMode(MOTOR_SIMULATION_RIGHT_BWD, OUTPUT);     

  pinMode(TRIGGER_PIN, OUTPUT);     
  pinMode(ECHO_PIN, INPUT);     

  if (fINIT_())
  {
    /* activation of drive loop */
  }
  else 
  {
    /* initialization failed, abort drive */
  }

}

void loop(void) {
  if(!bumper()){
    if(!avoider()){
      if(!finder()){
        ;
      }
    }
  }

  incrementTime();
}

boolean bumper(){
  switch(digitalRead(BUMPER_PIN)){
  case HIGH:
    Serial.println("BUMPER HIT");
    IN_.BumperInfo(C4_HITTED);
    return true;
  case LOW:
    //IN_.BumperInfo(C4_RELEASED);
    return false;
  }
  return false;
}

boolean avoider(){
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  /*
  Serial.print("MS: ");
   Serial.print(microsec);
   Serial.print(", CM: ");
   Serial.print(cmMsec);
   */
  if(cmMsec > 0 && cmMsec < 20){
    IN_.ObjectAvoidanceInfo(C5_DANGER);
  }
  else if(cmMsec >= 20 && cmMsec < 50){
    IN_.ObjectAvoidanceInfo(C5_ATTENTION);
  }
  else{
    IN_.ObjectAvoidanceInfo(C5_CLEAR);
    return false;
  }

  return true;
}

boolean finder(){
  int targetDirection = selectTargetDirection(
  analogRead(A0), 
  analogRead(A1));
  if(targetDirection == currentTargetDirectionMemento){
    return false;
  }

  IN_.PositionInfo(targetDirection);

  currentTargetDirectionMemento = targetDirection;
  return true;
}







int selectTargetDirection(int valLeft, int valRight){
  if(eq(valLeft,valRight)){
    return C1_Ahead;
  }

  if(valLeft > valRight){
    return C1_Left;
  }

  return C1_Right;
}

boolean targetFinder(){
  int numberpulses = listenForIR();

  Serial.print("Heard ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");
  if(numberpulses<21){
    return false;
  }

  if (IRcompare(numberpulses, IRsignal_LEFT_ChannelA)) {
    Serial.println("LEFT");
    notify(C1_Left);
  }

  if (IRcompare(numberpulses, IRsignal_RIGHT_ChannelA)) {
    Serial.println("RIGHT");
    notify(C1_Right);
  }

  if (IRcompare(numberpulses, IRsignal_FORWARD_FULL_ChannelA)) {
    Serial.println("AHEAD");
    notify(C1_Ahead);
  }

  if (IRcompare(numberpulses, IRsignal_STOP_ChannelA)) {
    Serial.println("STOP");
    notify(C1_Unknown);
  }

  return true;
}

void incrementTime(){
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  if (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
  Serial.println("TICK");
}

void on(int pin){
  digitalWrite(pin, HIGH);   // set the LED on
}
void off(int pin){
  digitalWrite(pin, LOW);   // set the LED off
}

void notify(unsigned char event){
  if(lastEvent == event){
    return;
  }

  IN_.PositionInfo(event);
  lastEvent = event;
}

extern "C" {


  void allLeftOff(){
    off(MOTOR_SIMULATION_LEFT_FWD);
    off(MOTOR_SIMULATION_LEFT_STOP);
    off(MOTOR_SIMULATION_LEFT_BWD);
  }
  void allRightOff(){
    off(MOTOR_SIMULATION_RIGHT_FWD);
    off(MOTOR_SIMULATION_RIGHT_STOP);
    off(MOTOR_SIMULATION_RIGHT_BWD);
  }

  void uCHAN_MotorLeftActions (unsigned char name_)
  {
    allLeftOff();
    /* Accessing MESSAGE */
    switch (name_)
    {
    case C2_BWD:
      on(MOTOR_SIMULATION_LEFT_BWD);
      //		motorLeft.run(BACKWARD); 
      break;
    case C2_FWD:
      on(MOTOR_SIMULATION_LEFT_FWD);
      //		motorLeft.run(FORWARD); 
      break;
    case C2_STOP:
      on(MOTOR_SIMULATION_LEFT_STOP);
      //		motorLeft.run(RELEASE); 
      break;
    default: 
      break;
    }
  }

  void uCHAN_MotorRightActions (unsigned char name_)
  {
    allRightOff();
    /* Accessing MESSAGE */
    switch (name_)
    {
    case C3_BWD:
      on(MOTOR_SIMULATION_RIGHT_BWD);
      //		motorRight.run(BACKWARD); 
      break;
    case C3_FWD:
      on(MOTOR_SIMULATION_RIGHT_FWD);
      //		motorRight.run(FORWARD); 
      break;
    case C3_STOP:
      on(MOTOR_SIMULATION_RIGHT_STOP);
      //		motorRight.run(RELEASE); 
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

    OUT_.MotorLeftActions = uCHAN_MotorLeftActions;
    OUT_.MotorRightActions = uCHAN_MotorRightActions;
  }

} // extern C

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
    } 
    else {
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
    } 
    else {
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

boolean eq(int a, int b){
  return ( abs(a - b) < 20 ) ;
}

