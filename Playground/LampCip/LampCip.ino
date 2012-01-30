extern "C"{
  #include "sTheUnit.h"
}

const int buttonPin = 12;
const int ledPin = 13;
int inSnapshot;

void setup(){
 // init
 inSnapshot = 0;
   // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT); 
  
 if(!fINIT_()){
	// Fehler in fININT ...
 }
}

void loop(){
  int in = digitalRead(12); 
//  if(in != inSnapshot){
//	inSnapshot = in;
	if(in == HIGH){
		IN_.Schalter(C2_Ein);	
	}else{
		IN_.Schalter(C2_Aus);	
	}
  //}

  
  TRG_.TICK_();  
  
  //delay(500);
}

void uCHAN_Lampe (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_Aus:
		digitalWrite(ledPin,LOW);
		break;
	case C2_Ein:
		digitalWrite(ledPin,HIGH);
		break;
	default: 
		break;
	}
}
