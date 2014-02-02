#include "Arduino.h"
#include "Stair.h"

Stair::Stair()
: step01(2), step02(3),
step03(4),
step04(5),
step05(6),
step06(7),
step07(8),
step08(9),
step09(10),
step10(11),
step11(12),
step12(46),
step13(44),
step14(45),
maxSteps(14)
{

}

void Stair::fadeIn()
{
  Step steps[] = {step01, step02, step03, step04, step05, step06, step07, step08, step09, step10, step11, step12, step13, step14};
  for(int fadeValue = 0; fadeValue <= 255; fadeValue+=5){
    for(int i=0; i<maxSteps; i++){
      steps[i].fadeTo(fadeValue);
    }
    delay(10);
  }
}

void Stair::onTopDown()
{
  Step steps[] = {step01, step02, step03, step04, step05, step06, step07, step08, step09, step10, step11, step12, step13, step14};
  for(int s = maxSteps - 1; s >= 0; s--){
    steps[s].on();
    delay(150);  
  }
}

void Stair::fadeTopDown()
{
  Step steps[] = {step01, step02, step03, step04, step05, step06, step07, step08, step09, step10, step11, step12, step13, step14};
  for(int s = maxSteps - 1; s >= 0; s--){
    for(int value = 0; value<=255; value+=5){
      steps[s].fadeTo(value);
      delay(10);  
    }
    //delay(150);  
  }
}

void Stair::on()
{
  Step steps[] = {step01, step02, step03, step04, step05, step06, step07, step08, step09, step10, step11, step12, step13, step14};
  for(int i=0; i<maxSteps; i++){
    steps[i].on();
  }
}

void Stair::off()
{
  Step steps[] = {step01, step02, step03, step04, step05, step06, step07, step08, step09, step10, step11, step12, step13, step14};
  for(int i=0; i<maxSteps; i++){
    steps[i].off();
  }
}
