
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS AmbientLightDimmer
	Filename: AmbientLightDimmer.c
	generated by CIP Tool(R) Version 4.41.00
		February 15, 2015  10:53:56 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_AmbientLightDimmer.write_access_
#define STATUS status_AmbientLightDimmer.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Fade_In 1
#define Fade_Out 2
#define Off 3
#define On 4


/* INPULSES */
#define IP_FADE_IN 1
#define IP_FADE_OUT 2
#define TIMEUP_ 3


/* OUTPULSES */

#define O5_OFF 8
#define O5_ON 7
#define O3_OFF 2
#define O3_ON 1
#define O8_IS_OFF 17
#define O8_IS_ON 18
#define O8_TURN_OFF 16
#define O8_TURN_OFF_STEP 14
#define O8_TURN_ON 15
#define O8_TURN_ON_STEP 13
#define O1_IS_OFF 6
#define O1_IS_ON 5
#define O9_PRESS 20
#define O6_PRESS 9
#define O2_OFF 4
#define O2_ON 3

/* External Declarations */

extern unsigned long time_mTheUnit;
extern struct tTMQE_mTheUnit *tuhead_mTheUnit, *tutail_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;
extern struct tTIMING_mTheUnit TIMING_mTheUnit[3];

void fUPDATE_Lights (void);
void fSETTIM_mTheUnit (unsigned long *delay_, struct tTMEL_mTheUnit *timer_, struct tTMQE_mTheUnit *timeup_);
void fSTOPTIM_mTheUnit (struct tTMEL_mTheUnit *timer_, struct tTMQE_mTheUnit *timeup_);

/* Global Declarations */

static unsigned long delay_;
struct tPRINST_AmbientLightDimmer IO_AmbientLightDimmer;
union tSTATUS_AmbientLightDimmer status_AmbientLightDimmer;

/* Function Prototypes */

void fICHAN_AmbientDimReply (unsigned char name_);
int fPULSE_AmbientLightDimmer (unsigned char name_);
void fINIT_AmbientLightDimmer (void);

/* Input Channel Functions */

void fICHAN_AmbientDimReply (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE IS_OFF of INPORT AmbientDimmerEvents  ***/
	case C5_IS_OFF:
		switch (status_AmbientLightDimmer.read_access_.STATE)
		{
		case 2:  /* STATE Fade_Out */
			status_AmbientLightDimmer.write_access_.STATE = 3;  /* STATE Off */
			fSTOPTIM_mTheUnit (&IO_AmbientLightDimmer.timer_, 
				&IO_AmbientLightDimmer.timeup_);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE IS_ON of INPORT AmbientDimmerEvents  ***/
	case C5_IS_ON:
		switch (status_AmbientLightDimmer.read_access_.STATE)
		{
		case 1:  /* STATE Fade_In */
			status_AmbientLightDimmer.write_access_.STATE = 4;  /* STATE On */
			fSTOPTIM_mTheUnit (&IO_AmbientLightDimmer.timer_, 
				&IO_AmbientLightDimmer.timeup_);
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Lights ();
	return;
}

#undef EXCEPTION

int fPULSE_AmbientLightDimmer (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE FADE_IN  ***/
	case O5_ON:		/***  PULSE CAST from PROCESS AmbientLight  ***/
		switch (status_AmbientLightDimmer.read_access_.STATE)
		{
		case 2:  /* STATE Fade_Out */
			{
				delay_ =  3;	/***  DELAY AMBIENT_DIM_IN_DELAY  ***/
				status_AmbientLightDimmer.write_access_.STATE = 1;  /* STATE Fade_In */
				CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_PLUS;
				OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_AmbientLightDimmer.timer_, 
					&IO_AmbientLightDimmer.timeup_);
			}
			break;
		case 3:  /* STATE Off */
			{
				delay_ =  3;	/***  DELAY AMBIENT_DIM_IN_DELAY  ***/
				status_AmbientLightDimmer.write_access_.STATE = 1;  /* STATE Fade_In */
				CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_PLUS;
				OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_AmbientLightDimmer.timer_, 
					&IO_AmbientLightDimmer.timeup_);
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FADE_OUT  ***/
	case O5_OFF:		/***  PULSE CAST from PROCESS AmbientLight  ***/
		switch (status_AmbientLightDimmer.read_access_.STATE)
		{
		case 1:  /* STATE Fade_In */
			{
				delay_ =  5;	/***  DELAY AMBIENT_DIM_OUT_DELA  ***/
				status_AmbientLightDimmer.write_access_.STATE = 2;  /* STATE Fade_Out */
				CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_MINUS;
				OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_AmbientLightDimmer.timer_, 
					&IO_AmbientLightDimmer.timeup_);
			}
			break;
		case 4:  /* STATE On */
			{
				delay_ =  5;	/***  DELAY AMBIENT_DIM_OUT_DELA  ***/
				status_AmbientLightDimmer.write_access_.STATE = 2;  /* STATE Fade_Out */
				CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_MINUS;
				OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_AmbientLightDimmer.timer_, 
					&IO_AmbientLightDimmer.timeup_);
			}
			break;
		default: 
			break;
		}
		break;
	default: 
		return 0;
	}
	return 1;
}

/* Timer Functions */

static void fTICK_AmbientLightDimmer (void)
{
	if (IO_AmbientLightDimmer.timer_.set_ && 
		IO_AmbientLightDimmer.timer_.end_ == time_mTheUnit)
	{
		IO_AmbientLightDimmer.timer_.set_ = FALSE;
		--TIMING_mTheUnit[0].set_;
		if (tuhead_mTheUnit != &IO_AmbientLightDimmer.timeup_ && 
			!IO_AmbientLightDimmer.timeup_.preced_ && 
			!IO_AmbientLightDimmer.timeup_.next_)
		{
			if (! tuhead_mTheUnit)
				tuhead_mTheUnit = tutail_mTheUnit = &IO_AmbientLightDimmer.timeup_;
			else 
			{
				tutail_mTheUnit->next_ = &IO_AmbientLightDimmer.timeup_;
				IO_AmbientLightDimmer.timeup_.preced_ = tutail_mTheUnit;
				tutail_mTheUnit = &IO_AmbientLightDimmer.timeup_;
			}
		}
	}
}

static void fTUHNDL_AmbientLightDimmer (void)
{
	struct tTMQE_mTheUnit *element_ = tuhead_mTheUnit;
	if (tuhead_mTheUnit == tutail_mTheUnit)
		tuhead_mTheUnit = tutail_mTheUnit = 0;
	else 
	{
		tuhead_mTheUnit = element_->next_;
		element_->next_ = 0;
		tuhead_mTheUnit->preced_ = 0;
	}
	switch (status_AmbientLightDimmer.read_access_.STATE)
	{
	case 1:  /* STATE Fade_In */
		{
			delay_ =  3;	/***  DELAY AMBIENT_DIM_IN_DELAY  ***/
			status_AmbientLightDimmer.write_access_.STATE = 1;  /* STATE Fade_In */
			CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_PLUS;
			OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
			fSETTIM_mTheUnit (&delay_, 
				&IO_AmbientLightDimmer.timer_, 
				&IO_AmbientLightDimmer.timeup_);
		}
		break;
	case 2:  /* STATE Fade_Out */
		{
			delay_ =  5;	/***  DELAY AMBIENT_DIM_OUT_DELA  ***/
			status_AmbientLightDimmer.write_access_.STATE = 2;  /* STATE Fade_Out */
			CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_ = C4_MINUS;
			OUT_.AmbientDimAction (CHNOUT_mTheUnit.CHAN_AmbientDimAction.name_);
			fSETTIM_mTheUnit (&delay_, 
				&IO_AmbientLightDimmer.timer_, 
				&IO_AmbientLightDimmer.timeup_);
		}
		break;
	default: 
		break;
	}
	fUPDATE_Lights ();
}

/* Process Initialization Function */

void fINIT_AmbientLightDimmer (void)
{
	status_AmbientLightDimmer.write_access_.STATE = 3;  /* STATE Off */
	IO_AmbientLightDimmer.timer_.set_ = FALSE;
	IO_AmbientLightDimmer.timeup_.preced_ = 0;
	IO_AmbientLightDimmer.timeup_.next_ = 0;
	IO_AmbientLightDimmer.timeup_.proctype_ = 0;
	TIMING_mTheUnit[0].tkhndl_ = fTICK_AmbientLightDimmer;
	TIMING_mTheUnit[0].tuhndl_ = fTUHNDL_AmbientLightDimmer;
}

/*********************************************************************
	End of Module for PROCESS AmbientLightDimmer
*********************************************************************/
