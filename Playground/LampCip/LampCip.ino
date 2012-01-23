#include <sTheUnit.h>

int inSnapshot;

void setup(){
 // init
 inSnapshot = 0;
 if(!fINIT_()){
	// Fehler in fININT ...
 }
}

void loop(){
  int in = digitalRead(13); 
  if(in != inSnapshot){
	inSnapshot = in;
	if(in == HIGH){
		IN_.Schalter(C2_Ein);	
	}else{
		IN_.Schalter(C2_Aus);	
	}
  }

  
  TRG_.TICK_();  
  
  delay(500);
}
