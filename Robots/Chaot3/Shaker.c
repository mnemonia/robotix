
/*********************************************************************
	SYSTEM Chaot
	Module for PROCESS Shaker
	Filename: Shaker.c
	generated by CIP Tool(R) Version 4.41.00
		April 27, 2012  2:32:31 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mChaotUnit.h"

/* Process Macro Definitions */

#define SELF status_Shaker.write_access_
#define STATUS status_Shaker.read_access_
#define TIME time_mChaotUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Eight 1
#define Fifth 2
#define First 3
#define Forth 4
#define On 5
#define Second 6
#define Seventh 7
#define Sixt 8
#define Third 9


/* INPULSES */
#define IP_SHAKE 1
#define TIMEUP_ 2


/* OUTPULSES */

#define O5_DONE 7
#define O3_SHAKE 1
#define O3_START 6
#define O2_INDICATING 5
#define O4_MEASURED 4
#define O1_DONE 3

/* External Declarations */

extern unsigned long time_mChaotUnit;
extern struct tTMQE_mChaotUnit *tuhead_mChaotUnit, *tutail_mChaotUnit;
extern union tCHNOUT_mChaotUnit CHNOUT_mChaotUnit;
extern struct tTIMING_mChaotUnit TIMING_mChaotUnit;

void fUPDATE_Robot (void);
int fPULSE_Chaotic (unsigned char name_);
void fSETTIM_mChaotUnit (unsigned long *delay_, struct tTMEL_mChaotUnit *timer_, struct tTMQE_mChaotUnit *timeup_);
void fSTOPTIM_mChaotUnit (struct tTMEL_mChaotUnit *timer_, struct tTMQE_mChaotUnit *timeup_);

/* Global Declarations */

static unsigned long delay_;
struct tPRINST_Shaker IO_Shaker;
union tSTATUS_Shaker status_Shaker;

/* Function Prototypes */

int fPULSE_Shaker (unsigned char name_);
void fINIT_Shaker (void);

/* Input Channel Functions */

int fPULSE_Shaker (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE SHAKE  ***/
	case O3_SHAKE:		/***  PULSE CAST from PROCESS Controller  ***/
	case O3_START:
		switch (status_Shaker.read_access_.STATE)
		{
		case 5:  /* STATE On */
			{
				delay_ =  10;	/***  DELAY SHORT  ***/
				status_Shaker.write_access_.STATE = 3;  /* STATE First */
				CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_LEFT;
				OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
				fSETTIM_mChaotUnit (&delay_, 
					&IO_Shaker.timer_, 
					&IO_Shaker.timeup_);
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

static void fTICK_Shaker (void)
{
	if (IO_Shaker.timer_.set_ && 
		IO_Shaker.timer_.end_ == time_mChaotUnit)
	{
		IO_Shaker.timer_.set_ = FALSE;
		--TIMING_mChaotUnit.set_;
		if (tuhead_mChaotUnit != &IO_Shaker.timeup_ && 
			!IO_Shaker.timeup_.preced_ && 
			!IO_Shaker.timeup_.next_)
		{
			if (! tuhead_mChaotUnit)
				tuhead_mChaotUnit = tutail_mChaotUnit = &IO_Shaker.timeup_;
			else 
			{
				tutail_mChaotUnit->next_ = &IO_Shaker.timeup_;
				IO_Shaker.timeup_.preced_ = tutail_mChaotUnit;
				tutail_mChaotUnit = &IO_Shaker.timeup_;
			}
		}
	}
}

static void fTUHNDL_Shaker (void)
{
	struct tTMQE_mChaotUnit *element_ = tuhead_mChaotUnit;
	if (tuhead_mChaotUnit == tutail_mChaotUnit)
		tuhead_mChaotUnit = tutail_mChaotUnit = 0;
	else 
	{
		tuhead_mChaotUnit = element_->next_;
		element_->next_ = 0;
		tuhead_mChaotUnit->preced_ = 0;
	}
	switch (status_Shaker.read_access_.STATE)
	{
	case 1:  /* STATE Eight */
		status_Shaker.write_access_.STATE = 5;  /* STATE On */
		CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_CENTER;
		OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
		fPULSE_Chaotic (O1_DONE);
		break;
	case 2:  /* STATE Fifth */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 8;  /* STATE Sixt */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_RIGHT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 3:  /* STATE First */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 6;  /* STATE Second */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_RIGHT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 4:  /* STATE Forth */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 2;  /* STATE Fifth */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_LEFT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 6:  /* STATE Second */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 9;  /* STATE Third */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_LEFT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 7:  /* STATE Seventh */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 1;  /* STATE Eight */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_RIGHT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 8:  /* STATE Sixt */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 7;  /* STATE Seventh */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_LEFT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	case 9:  /* STATE Third */
		{
			delay_ =  25;	/***  DELAY LONG  ***/
			status_Shaker.write_access_.STATE = 4;  /* STATE Forth */
			CHNOUT_mChaotUnit.CHAN_ShakerActions.name_ = C2_RIGHT;
			OUT_.ShakerActions (CHNOUT_mChaotUnit.CHAN_ShakerActions.name_);
			fSETTIM_mChaotUnit (&delay_, 
				&IO_Shaker.timer_, 
				&IO_Shaker.timeup_);
		}
		break;
	default: 
		break;
	}
	fUPDATE_Robot ();
}

/* Process Initialization Function */

void fINIT_Shaker (void)
{
	status_Shaker.write_access_.STATE = 5;  /* STATE On */
	IO_Shaker.timer_.set_ = FALSE;
	IO_Shaker.timeup_.preced_ = 0;
	IO_Shaker.timeup_.next_ = 0;
	IO_Shaker.timeup_.proctype_ = 0;
	TIMING_mChaotUnit.tkhndl_ = fTICK_Shaker;
	TIMING_mChaotUnit.tuhndl_ = fTUHNDL_Shaker;
}

/*********************************************************************
	End of Module for PROCESS Shaker
*********************************************************************/
