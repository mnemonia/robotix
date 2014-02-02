#ifndef Stair_h
#define Stair_h

#include "Arduino.h"
#include "Step.h"

class Stair
{
  public:
    Stair();
    void fadeIn();
    void fadeTopDown();
    void onTopDown();
    void on();
    void off();
  private:
  	Step step01;
	Step step02;
	Step step03;
	Step step04;
	Step step05;
	Step step06;
	Step step07;
	Step step08;
	Step step09;
	Step step10;
	Step step11;
	Step step12;
	Step step13;
	Step step14;
        int maxSteps;
    //Step steps[];
};

#endif
