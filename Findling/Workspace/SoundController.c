
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS SoundController
	Filename: SoundController.c
	generated by CIP Tool(R) Version 4.41.00
		February 18, 2015  2:26:12 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_SoundController.write_access_
#define STATUS status_SoundController.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define automatic 1
#define manual 2

/* STATES */
#define Off 1
#define On 2
#define TurningOff 3
#define TurningOn 4


/* INPULSES */
#define IP_FADE_IN 1
#define IP_FADE_OUT 2
#define TIMEUP_ 3
#define IP_FADE_IN_STEP 4
#define IP_FADE_OUT_STEP 5


/* OUTPULSES */

#define O14_IS_OFF 8
#define O14_IS_ON 7
#define O12_PRESSED 1
#define O12_RELEASED 2
#define O13_PRESSED 3
#define O10_OFF 6
#define O10_ON 5

/* External Declarations */

extern unsigned long time_mTheUnit;
extern struct tTMQE_mTheUnit *tuhead_mTheUnit, *tutail_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;
extern struct tTIMING_mTheUnit TIMING_mTheUnit[4];
extern union tSTATUS_SoundMinusButton status_SoundMinusButton;
extern union tSTATUS_SoundPlusButton status_SoundPlusButton;
extern union tSTATUS_SoundSwitch status_SoundSwitch;

void fUPDATE_Sound (void);
int fPULSE_SoundSwitch (unsigned char name_);
void fSETTIM_mTheUnit (unsigned long *delay_, struct tTMEL_mTheUnit *timer_, struct tTMQE_mTheUnit *timeup_);
void fSTOPTIM_mTheUnit (struct tTMEL_mTheUnit *timer_, struct tTMQE_mTheUnit *timeup_);

/* Global Declarations */

static unsigned long delay_;
struct tPRINST_SoundController IO_SoundController;
union tSTATUS_SoundController status_SoundController;
const unsigned char MODTAB_SoundController[2][2][4] =       /*  [SoundMinusButton states] [SoundPlusButton states] [SoundSwitch states] */
	{{{1, 1, 1, 1}, 
	{2, 2, 2, 2}}, 
	{{2, 2, 2, 2}, 
	{2, 2, 2, 2}}};

/* Function Prototypes */

void fICHAN_SoundControlEvents (unsigned char name_);
int fPULSE_SoundController (unsigned char name_);
void fINIT_SoundController (void);

/* Input Channel Functions */

void fICHAN_SoundControlEvents (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE IS_OFF of INPORT SoundControlEvents  ***/
	case C12_IS_OFF:
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE automatic */
			switch (status_SoundController.read_access_.STATE)
			{
			case 3:  /* STATE TurningOff */
				status_SoundController.write_access_.STATE = 1;  /* STATE Off */
				fSTOPTIM_mTheUnit (&IO_SoundController.timer_, 
					&IO_SoundController.timeup_);
				fPULSE_SoundSwitch (O14_IS_OFF);
				break;
			default: 
				return;
			}
			break;
		case 2:  /* MODE manual */
			switch (status_SoundController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_SoundController.write_access_.STATE = 1;  /* STATE Off */
				fPULSE_SoundSwitch (O14_IS_OFF);
				break;
			case 3:  /* STATE TurningOff */
				status_SoundController.write_access_.STATE = 1;  /* STATE Off */
				fPULSE_SoundSwitch (O14_IS_OFF);
				break;
			default: 
				return;
			}
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE IS_ON of INPORT SoundControlEvents  ***/
	case C12_IS_ON:
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE automatic */
			switch (status_SoundController.read_access_.STATE)
			{
			case 3:  /* STATE TurningOff */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_SoundSwitch (O14_IS_ON);
				break;
			case 4:  /* STATE TurningOn */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				fSTOPTIM_mTheUnit (&IO_SoundController.timer_, 
					&IO_SoundController.timeup_);
				fPULSE_SoundSwitch (O14_IS_ON);
				break;
			default: 
				return;
			}
			break;
		case 2:  /* MODE manual */
			switch (status_SoundController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_SoundSwitch (O14_IS_ON);
				break;
			case 4:  /* STATE TurningOn */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_SoundSwitch (O14_IS_ON);
				break;
			default: 
				return;
			}
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Sound ();
	return;
}

#undef EXCEPTION

int fPULSE_SoundController (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE FADE_IN  ***/
	case O10_ON:		/***  PULSE CAST from PROCESS SoundSwitch  ***/
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE automatic */
			switch (status_SoundController.read_access_.STATE)
			{
			case 1:  /* STATE Off */
				{
					delay_ =  1;	/***  DELAY SOUND_IN_DELAY  ***/
					status_SoundController.write_access_.STATE = 4;  /* STATE TurningOn */
					CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS;
					OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
					fSETTIM_mTheUnit (&delay_, 
						&IO_SoundController.timer_, 
						&IO_SoundController.timeup_);
				}
				break;
			case 3:  /* STATE TurningOff */
				{
					delay_ =  1;	/***  DELAY SOUND_IN_DELAY  ***/
					status_SoundController.write_access_.STATE = 4;  /* STATE TurningOn */
					CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS;
					OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
					fSETTIM_mTheUnit (&delay_, 
						&IO_SoundController.timer_, 
						&IO_SoundController.timeup_);
				}
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FADE_IN_STEP  ***/
	case O13_PRESSED:		/***  PULSE CAST from PROCESS SoundPlusButton  ***/
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE manual */
			switch (status_SoundController.read_access_.STATE)
			{
			case 1:  /* STATE Off */
				status_SoundController.write_access_.STATE = 4;  /* STATE TurningOn */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS_STEP;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				break;
			case 2:  /* STATE On */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				break;
			case 4:  /* STATE TurningOn */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS_STEP;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FADE_OUT  ***/
	case O10_OFF:		/***  PULSE CAST from PROCESS SoundSwitch  ***/
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE automatic */
			switch (status_SoundController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				{
					delay_ =  9;	/***  DELAY SOUND_OUT_DELAY  ***/
					status_SoundController.write_access_.STATE = 3;  /* STATE TurningOff */
					CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_MINUS;
					OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
					fSETTIM_mTheUnit (&delay_, 
						&IO_SoundController.timer_, 
						&IO_SoundController.timeup_);
				}
				break;
			case 4:  /* STATE TurningOn */
				{
					delay_ =  9;	/***  DELAY SOUND_OUT_DELAY  ***/
					status_SoundController.write_access_.STATE = 3;  /* STATE TurningOff */
					CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_MINUS;
					OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
					fSETTIM_mTheUnit (&delay_, 
						&IO_SoundController.timer_, 
						&IO_SoundController.timeup_);
				}
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FADE_OUT_STEP  ***/
	case O12_PRESSED:		/***  PULSE CAST from PROCESS SoundMinusButton  ***/
		switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE manual */
			switch (status_SoundController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_MINUS;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				break;
			case 3:  /* STATE TurningOff */
				status_SoundController.write_access_.STATE = 2;  /* STATE On */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_MINUS;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				break;
			default: 
				break;
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

static void fTICK_SoundController (void)
{
	if (IO_SoundController.timer_.set_ && 
		IO_SoundController.timer_.end_ == time_mTheUnit)
	{
		IO_SoundController.timer_.set_ = FALSE;
		--TIMING_mTheUnit[3].set_;
		if (tuhead_mTheUnit != &IO_SoundController.timeup_ && 
			!IO_SoundController.timeup_.preced_ && 
			!IO_SoundController.timeup_.next_)
		{
			if (! tuhead_mTheUnit)
				tuhead_mTheUnit = tutail_mTheUnit = &IO_SoundController.timeup_;
			else 
			{
				tutail_mTheUnit->next_ = &IO_SoundController.timeup_;
				IO_SoundController.timeup_.preced_ = tutail_mTheUnit;
				tutail_mTheUnit = &IO_SoundController.timeup_;
			}
		}
	}
}

static void fTUHNDL_SoundController (void)
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
	switch (MODTAB_SoundController[status_SoundMinusButton.read_access_.STATE -1][status_SoundPlusButton.read_access_.STATE -1][status_SoundSwitch.read_access_.STATE -1])
	{
	case 1:  /* MODE automatic */
		switch (status_SoundController.read_access_.STATE)
		{
		case 3:  /* STATE TurningOff */
			{
				delay_ =  9;	/***  DELAY SOUND_OUT_DELAY  ***/
				status_SoundController.write_access_.STATE = 3;  /* STATE TurningOff */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_MINUS;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_SoundController.timer_, 
					&IO_SoundController.timeup_);
			}
			break;
		case 4:  /* STATE TurningOn */
			{
				delay_ =  1;	/***  DELAY SOUND_IN_DELAY  ***/
				status_SoundController.write_access_.STATE = 4;  /* STATE TurningOn */
				CHNOUT_mTheUnit.CHAN_SoundActions.name_ = C11_PLUS;
				OUT_.SoundActions (CHNOUT_mTheUnit.CHAN_SoundActions.name_);
				fSETTIM_mTheUnit (&delay_, 
					&IO_SoundController.timer_, 
					&IO_SoundController.timeup_);
			}
			break;
		default: 
			break;
		}
		break;
	default: 
		break;
	}
	fUPDATE_Sound ();
}

/* Process Initialization Function */

void fINIT_SoundController (void)
{
	status_SoundController.write_access_.STATE = 1;  /* STATE Off */
	IO_SoundController.timer_.set_ = FALSE;
	IO_SoundController.timeup_.preced_ = 0;
	IO_SoundController.timeup_.next_ = 0;
	IO_SoundController.timeup_.proctype_ = 3;
	TIMING_mTheUnit[3].tkhndl_ = fTICK_SoundController;
	TIMING_mTheUnit[3].tuhndl_ = fTUHNDL_SoundController;
}

/*********************************************************************
	End of Module for PROCESS SoundController
*********************************************************************/
