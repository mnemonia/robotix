#include <AFMotor.h>
#include <Servo.h> 
#include <Ultrasonic.h>

int w1;
int w2;
int w3;

AF_DCMotor leftMotor(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor rightMotor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int theSpeed = 100;

void setup() {
  leftMotor.setSpeed(theSpeed);     // set the speed to 200/255
  rightMotor.setSpeed(theSpeed);     // set the speed to 200/255
}

void loop() {
 ping1();
 if(w1 < 100){
     check();
     if(w2 > w3){
         right();
     }else{
       left();
     } 
 }else {
     fwd();
 }
}

  
void fwd(){
  motor.run(FORWARD);      // turn it on going forward
  motor2.run(FORWARD);      // turn it on going forward
//	   pulsout 4,250
//	   pulsout 2,100	
}
	  
	  
void revs(){
	   for(int b0 = 0; i<30; i++){
  motor.run(BACKWARD);      // turn it on going forward
  motor2.run(BACKWARD);      // turn it on going forward
//	   pulsout 4,50
//	   pulsout 2,300	
	   delay(2);
            }
}	  
void left(){
	   for(int b0 = 0; i<65; i++){
  motor.run(BACKWARD);      // turn it on going forward
  motor2.run(FORWARD);      // turn it on going forward
//	   pulsout 4,300
//	   pulsout 2,300	 
	   delay(2);
            }
}
	   next b0
	   return
void right(){
	   for(int b0 = 0; i<65; i++){
  motor.run(FORWARD);      // turn it on going forward
  motor2.run(BACKWARD);      // turn it on going forward
//	   pulsout 4,50
//	   pulsout 2,50	 
    delay(2);
  }
}	  

void ping1(){

}
         for b0 = 0 to 20 	
	   pulsout 0,130	
	   pause 3
	   next b0
         pulsout 1,1
	   pulsin 3,1,w1
	   let w1= w1  * 34 /2 /10
	   return
ping2:
         for b0 = 0 to 30 	
	   pulsout 0,250	
	   pause 3
	   next b0
	   pause 200
         pulsout 1,1
	   pulsin 3,1,w2
	   let w2= w2  * 34 /2 /10
	   pause 20
	   return
ping3:
         for b0 = 0 to 50 	
	   pulsout 0,40
	   pause 2	
	   next b0
	   pause 200
         pulsout 1,1
	   pulsin 3,1,w3
	   let w3= w3  * 34 /2 /10
	   pause 20
	   return
check:
	   gosub ping2
	   gosub ping3
	   if w2< 100 and w3 < 100 then
             gosub revs
             gosub check
         endif     
	  return
