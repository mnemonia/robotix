/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int lightTriggerPin = 7;     // the number of the pushbutton pin
const int bellTriggerPin = 8;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int lightPin = 3;      // the number of the LED pin
const int bellPin = 5;      // the number of the LED pin
const int pirPin = 2;
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
  
  setupPir();
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
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    digitalWrite(lightPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
    digitalWrite(lightPin, LOW); 
  }

  // read the state of the pushbutton value:
  bellTriggerState = digitalRead(bellTriggerPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (bellTriggerState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    digitalWrite(bellPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
    digitalWrite(bellPin, LOW); 
  }

loopPir();
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
