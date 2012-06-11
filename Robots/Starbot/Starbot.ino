extern "C"{
#include "sStarbotUnit.h"
}
#include <Servo.h>

Servo myservo;
int pos = 0;    // variable to store the servo position 

int ldr1 = A2;
int ldr2 = A3;
int ldr3 = A4;
int ldr4 = A5;
int ldrPlus = 4;
int lights = 5;
int light = 8;

int threshold_1 = 108;
int threshold_2 = 150;
int threshold_3 = 110;
int threshold_4 = 100;
int thresholdAttraction = 50;

long currentMillies = 0L;
long previousMillis = 0;
long interval = 20;  

int detectionSensorValue = 0;

int sensorValue;

int starEdge = 11;
int starCenter = 13;

void setup() {                
  Serial.begin(9600);
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(ldrPlus,OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(starEdge, OUTPUT);
  pinMode(starCenter,OUTPUT);
    
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(90);

  on(ldrPlus);

  //on(light);   // set the LED on  
  //on(lights);
  
  if (fINIT_())
  {
  	IN_.StartChannel(C1_START);
  }
  else 
  {
  	/* initialization failed, abort drive */
  }  
}

void loop(){
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
   incrementTime();
  }  
}

void incrementTime(){
//  int sensorValue = analogRead(sensorPin);    

  
  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */
  
  while (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
//  Serial.println("TICK");
}

void loop2() {  
  sensorValue = analogRead(ldr1);  
Serial.print(sensorValue); 
Serial.print(" ");  

  if(sensorValue > threshold_1){
    //digitalWrite(indicator1,HIGH);
    myservo.write(60);
  }else{
    //digitalWrite(indicator1,LOW);
  }
  
  sensorValue = analogRead(ldr2);  
Serial.print(sensorValue); 
Serial.print(" ");  

  if(sensorValue > threshold_2){
    //digitalWrite(indicator2,HIGH);
    myservo.write(80);
  }else{
    //digitalWrite(indicator2,LOW);
  }

  sensorValue = analogRead(ldr3);  
Serial.print(sensorValue); 
Serial.print(" ");  

  if(sensorValue > threshold_3){
    //digitalWrite(indicator3,HIGH);
    myservo.write(100);
  }else{
    //digitalWrite(indicator3,LOW);
  }

  sensorValue = analogRead(ldr4);  
Serial.println(sensorValue); 

  if(sensorValue > threshold_4){
    //digitalWrite(indicator4,HIGH);
    myservo.write(120);
  }else{
    //digitalWrite(indicator4,LOW);
  }
//delay(50);  
/*  
  digitalWrite(13, HIGH);   // set the LED on
  for(pos = 5; pos < 175; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  delay(1000);          
  digitalWrite(13, LOW);
  delay(1000);          
  digitalWrite(13, HIGH);
  for(pos = 175; pos>=5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  digitalWrite(13, LOW);
  delay(1000);
*/
}
void on(int pin){
  digitalWrite(pin,HIGH);
}
void off(int pin){
  digitalWrite(pin,LOW);
}
extern "C" {
  /* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_ShineChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_END:
		/* user defined code */
		break;
	case C2_SHINE:
		on(starCenter);
                on(starEdge);
		break;
	default: 
		break;
	}
}

void uCHAN_AttrackChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_ATTRACK:
		on(light);
		break;
	default: 
		break;
	}
}

void uCHAN_DetectChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_DETECT_PLAYER:
                detectionSensorValue = analogRead(ldr2);
                Serial.println(detectionSensorValue);
                if(detectionSensorValue > thresholdAttraction){
Serial.println("C5_DETECTED_PLAYER ");
                  IN_.DetectionChannel(C5_DETECTED_PLAYER);
                }
		break;
	default: 
		break;
	}
}



void uCHAN_TrackOutChannel (unsigned char name_)
{
        off(lights);
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C6_TRACK_CENTER:
                myservo.write(90);
		break;
	case C6_TRACK_LEFT:
                myservo.write(60);
		break;
	case C6_TRACK_PLAYER:
                on(lights);
                sensorValue = analogRead(ldr1);  
              Serial.print(sensorValue); 
              Serial.print(" ");  
              
                if(sensorValue > threshold_1){
                  IN_.TrackInChannel(C7_LEFT);
                  return;
                }
                
                sensorValue = analogRead(ldr2);  
              Serial.print(sensorValue); 
              Serial.print(" ");  
              
                if(sensorValue > threshold_2){
                  IN_.TrackInChannel(C7_CENTER);
                  return;
                }
              
                sensorValue = analogRead(ldr3);  
              Serial.print(sensorValue); 
              Serial.print(" ");  
              
                if(sensorValue > threshold_3){
                  IN_.TrackInChannel(C7_CENTER);
                  return;
                }
              
                sensorValue = analogRead(ldr4);  
              Serial.println(sensorValue); 
              
                if(sensorValue > threshold_4){
                  IN_.TrackInChannel(C7_RIGHT);
                  return;
                }
                break;
	case C6_TRACK_RIGHT:
                myservo.write(120);
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

	OUT_.AttrackChannel = uCHAN_AttrackChannel;
	OUT_.DetectChannel = uCHAN_DetectChannel;
	OUT_.ShineChannel = uCHAN_ShineChannel;
	OUT_.TrackOutChannel = uCHAN_TrackOutChannel;
}


}
