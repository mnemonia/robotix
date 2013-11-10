
/*********************************************************************
	SYSTEM FrontDoor
	Module for PROCESS BellSwitch
	Filename: BellSwitch.c
	generated by CIP Tool(R) Version 4.41.00
		November 10, 2013  9:40:45 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned int' for delays
		C-code
*********************************************************************/

/* Include Files */

#include "mArduinoUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_BellSwitch.write_access_
#define STATUS status_BellSwitch.read_access_
#define TIME time_mArduinoUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Quiet 1
#define Ringing 2


/* INPULSES */
#define TIMEUP_ 1


/* OUTPULSES */

#define O3_OFF 4
#define O3_ON 3
#define O2_DOWN 1
#define O2_UP 2

/* External Declarations */

extern unsigned int time_mArduinoUnit;
extern struct tTMQE_mArduinoUnit *tuhead_mArduinoUnit, *tutail_mArduinoUnit;
extern union tCHNOUT_mArduinoUnit CHNOUT_mArduinoUnit;
extern struct tTIMING_mArduinoUnit TIMING_mArduinoUnit;

void fUPDATE_Sonnerie (void);
int fPULSE_Bell (unsigned char name_);
void fSETTIM_mArduinoUnit (unsigned int *delay_, struct tTMEL_mArduinoUnit *timer_, struct tTMQE_mArduinoUnit *timeup_);
void fSTOPTIM_mArduinoUnit (struct tTMEL_mArduinoUnit *timer_, struct tTMQE_mArduinoUnit *timeup_);

/* Global Declarations */

static unsigned int delay_;
struct tPRINST_BellSwitch IO_BellSwitch;
union tSTATUS_BellSwitch status_BellSwitch;

/* Function Prototypes */

void fICHAN_BellInChannel (unsigned char name_);
void fINIT_BellSwitch (void);

/* Input Channel Functions */

void fICHAN_BellInChannel (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE DOWN of INPORT BellInport  ***/
	case C3_DOWN:
		switch (status_BellSwitch.read_access_.STATE)
		{
		case 1:  /* STATE Quiet */
			{
				delay_ =  30;	/***  DELAY RingingDuration  ***/
				status_BellSwitch.write_access_.STATE = 2;  /* STATE Ringing */
				fSETTIM_mArduinoUnit (&delay_, 
					&IO_BellSwitch.timer_, 
					&IO_BellSwitch.timeup_);
				fPULSE_Bell (O3_ON);
			}
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Sonnerie ();
	return;
}

#undef EXCEPTION

/* Timer Functions */

static void fTICK_BellSwitch (void)
{
	if (IO_BellSwitch.timer_.set_ && 
		IO_BellSwitch.timer_.end_ == time_mArduinoUnit)
	{
		IO_BellSwitch.timer_.set_ = FALSE;
		--TIMING_mArduinoUnit.set_;
		if (tuhead_mArduinoUnit != &IO_BellSwitch.timeup_ && 
			!IO_BellSwitch.timeup_.preced_ && 
			!IO_BellSwitch.timeup_.next_)
		{
			if (! tuhead_mArduinoUnit)
				tuhead_mArduinoUnit = tutail_mArduinoUnit = &IO_BellSwitch.timeup_;
			else 
			{
				tutail_mArduinoUnit->next_ = &IO_BellSwitch.timeup_;
				IO_BellSwitch.timeup_.preced_ = tutail_mArduinoUnit;
				tutail_mArduinoUnit = &IO_BellSwitch.timeup_;
			}
		}
	}
}

static void fTUHNDL_BellSwitch (void)
{
	struct tTMQE_mArduinoUnit *element_ = tuhead_mArduinoUnit;
	if (tuhead_mArduinoUnit == tutail_mArduinoUnit)
		tuhead_mArduinoUnit = tutail_mArduinoUnit = 0;
	else 
	{
		tuhead_mArduinoUnit = element_->next_;
		element_->next_ = 0;
		tuhead_mArduinoUnit->preced_ = 0;
	}
	switch (status_BellSwitch.read_access_.STATE)
	{
	case 2:  /* STATE Ringing */
		status_BellSwitch.write_access_.STATE = 1;  /* STATE Quiet */
		fPULSE_Bell (O3_OFF);
		break;
	default: 
		break;
	}
	fUPDATE_Sonnerie ();
}

/* Process Initialization Function */

void fINIT_BellSwitch (void)
{
	status_BellSwitch.write_access_.STATE = 1;  /* STATE Quiet */
	IO_BellSwitch.timer_.set_ = FALSE;
	IO_BellSwitch.timeup_.preced_ = 0;
	IO_BellSwitch.timeup_.next_ = 0;
	IO_BellSwitch.timeup_.proctype_ = 0;
	TIMING_mArduinoUnit.tkhndl_ = fTICK_BellSwitch;
	TIMING_mArduinoUnit.tuhndl_ = fTUHNDL_BellSwitch;
}

/*********************************************************************
	End of Module for PROCESS BellSwitch
*********************************************************************/
