extern "C" {
  #include "sArduinoUnit.h"
}

const int lightTriggerPin = 7;     // the number of the pushbutton pin
const int bellTriggerPin = 8;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int lightPin = 3;      // the number of the LED pin
const int bellPin = 5;      // the number of the LED pin
const int pirPin = 2;

long currentMillies = 0L;
long previousMillis = 0L;
long interval = 20L;  

/////////////////////////////
//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

// variables will change:
int lightTriggerState = 0;         // variable for reading the pushbutton status
int bellTriggerState = 0;         // variable for reading the pushbutton status


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the LED pin as an output:
  pinMode(lightPin, OUTPUT);      
  pinMode(bellPin, OUTPUT);      
  
  // initialize the pushbutton pin as an input:
  pinMode(lightTriggerPin, INPUT); 
  pinMode(bellTriggerPin, INPUT); 

  digitalWrite(ledPin, LOW); 
  digitalWrite(lightPin, LOW); 
  
//  setupPir();
  
  
  /*********************************************************************
  	Execution of CIP Connector Activities
  *********************************************************************/
  
  	/* Initializing CIP Machine */
  
  if (fINIT_())
  {
  	/* activation of drive loop */
  }
  else 
  {
  	/* initialization failed, abort drive */
  }
  
}

void setupPir(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}

void loop(){
  // read the state of the pushbutton value:
  lightTriggerState = digitalRead(lightTriggerPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (lightTriggerState == HIGH) {     
    IN_.LightSwitchInChannel(C1_DOWN);
  } 
  else {
    IN_.LightSwitchInChannel(C1_UP);    
  }
  
//  delay(25);


  // read the state of the pushbutton value:
  bellTriggerState = digitalRead(bellTriggerPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (bellTriggerState == HIGH) {     
    IN_.BellInChannel(C3_DOWN);
  } 
  else {
    // IN_.BellInChannel(C3_SWITCH);
  }

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
    incrementTime();
  }  

//loopPir();

}

void incrementTime(){
  //  int sensorValue = analogRead(sensorPin);    

  TRG_.TICK_(); 		/* increment CIP Machine time by one Tick */

  while (TRG_.PENDING_.TIMEUP_) TRG_.TIMEUP_(); /* timeup call */
  //  Serial.println("TICK");
}

void loopPir(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         digitalWrite(lightPin, HIGH);
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
  
  
  extern "C" {
  /*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

void uCHAN_BellOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_OFF:
                digitalWrite(ledPin, LOW);  
                digitalWrite(bellPin, LOW);  
		break;
	case C4_ON:
                digitalWrite(ledPin, HIGH);  
                digitalWrite(bellPin, HIGH);  
		break;
	default: 
		break;
	}
}

void uCHAN_LightOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_OFF:
                digitalWrite(ledPin, LOW);  
                digitalWrite(lightPin, LOW);  
		break;
	case C2_ON:
                digitalWrite(ledPin, HIGH);  
                digitalWrite(lightPin, HIGH);  
		break;
	default: 
		break;
	}
}


/*********************************************************************
	User defined Output Channel Interface Initialization Function
*********************************************************************/

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.BellOutChannel = uCHAN_BellOutChannel;
	OUT_.LightOutChannel = uCHAN_LightOutChannel;
}


}
