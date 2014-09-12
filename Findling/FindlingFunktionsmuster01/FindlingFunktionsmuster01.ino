#include <CapacitiveSensor.h>
//#include <Servo.h> 

//Servo swipeServo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
//int swipeServoPosition = 0;    // variable to store the servo position 

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
//   swipeServo.attach(3);  // attaches the servo on pin 9 to the servo object 
//   swipeServo.write(swipeServoPosition);
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()                    
{
  singleTouch();
  doubleTouch();
//  doubleTouchWithSwipe();
  delay(10);                             // arbitrary delay to limit data to serial port 
}

void servoRotate(int toPosition){
    //myservo.write(toPosition);
}

long capTouch(long minCapValue, long maxCapValue, long capValue, int actorPin, int scaleMin, int scaleMax){
    long start = millis();
    Serial.println(capValue);
    if(capValue > minCapValue){
      if(capValue > maxCapValue){
        return 1023;
      }else{
        long capValueScaled = map(capValue, minCapValue, maxCapValue, scaleMin, scaleMax);
        return capValueScaled;
      }
    }
    return 0;
}
void light(long capValue, int actorPin){
    analogWrite(actorPin, capValue);
}

void oldCapTouch(long minCapValue, long maxCapValue, long capValue, int actorPin){
    long start = millis();
    Serial.println(capValue);
    if(capValue > minCapValue){
      if(capValue > maxCapValue){
        analogWrite(actorPin, 1023);
      }else{
        long capValueScaled = map(capValue, minCapValue, maxCapValue, 0, 1023);
        analogWrite(actorPin, capValueScaled);
      }
    }else{
      analogWrite(actorPin, 0);
    }
}

void singleTouch(){
    long minCapValue = 15000;
    long maxCapValue = 180000;
    long capSensorValue =  cs_4_2.capacitiveSensor(30);
    int actorPin = 9;
    int capValue = capTouch(minCapValue, maxCapValue, capSensorValue, actorPin, 0, 1023);
    light(capValue, actorPin);
}


void oldSingleTouch(){
    long minCapValue = 15000;
    long maxCapValue = 180000;
    long capValue =  cs_4_2.capacitiveSensor(30);
    int actorPin = 9;
   // capTouch(minCapValue, maxCapValue, capValue, actorPin);
}

void doubleTouch(){
    long minCapValue = 500;
    long maxCapValue = 15000;
    long capValueLeft =  cs_4_6.capacitiveSensor(30);
    long capValueRight =  cs_4_8.capacitiveSensor(30);
    int actorPinLeft = 10;
    int actorPinRight = 11;
    int capLeft = capTouch(minCapValue, maxCapValue, capValueLeft, actorPinLeft, 0, 1023);
    int capRight = capTouch(minCapValue, maxCapValue, capValueRight, actorPinRight, 0, 1023);
    light(capLeft, actorPinLeft);
    light(capRight, actorPinRight);
}


