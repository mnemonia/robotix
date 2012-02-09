
/*********************************************************************
	SYSTEM BabyAlarm
	Module for PROCESS PrimitiveBehavior
	Filename: PrimitiveBehavior.c
	generated by CIP Tool(R) Version 4.41.00
		February 9, 2012  3:36:10 am
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_PrimitiveBehavior.write_access_
#define STATUS status_PrimitiveBehavior.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define Alarm 1
#define Info 2
#define On 3
#define Recording 4
#define Warning 5



/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;


/* Global Declarations */

union tSTATUS_PrimitiveBehavior status_PrimitiveBehavior;

/* Function Prototypes */

void fICHAN_Record (unsigned char name_);
void fICHAN_Surveillance (unsigned char name_);
void fINIT_PrimitiveBehavior (void);

/* Input Channel Functions */

void fICHAN_Record (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE Done of INPORT Record  ***/
	case C3_Done:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case 4:  /* STATE Recording */
			status_PrimitiveBehavior.write_access_.STATE = 3;  /* STATE On */
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Recording of INPORT Record  ***/
	case C3_Recording:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case 1:  /* STATE Alarm */
			status_PrimitiveBehavior.write_access_.STATE = 4;  /* STATE Recording */
			break;
		case 2:  /* STATE Info */
			status_PrimitiveBehavior.write_access_.STATE = 4;  /* STATE Recording */
			break;
		case 3:  /* STATE On */
			status_PrimitiveBehavior.write_access_.STATE = 4;  /* STATE Recording */
			break;
		case 5:  /* STATE Warning */
			status_PrimitiveBehavior.write_access_.STATE = 4;  /* STATE Recording */
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	return;
}

void fICHAN_Surveillance (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE Loud of INPORT Noise  ***/
	case C1_Loud:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case 2:  /* STATE Info */
			status_PrimitiveBehavior.write_access_.STATE = 5;  /* STATE Warning */
			break;
		case 3:  /* STATE On */
			status_PrimitiveBehavior.write_access_.STATE = 2;  /* STATE Info */
			CHNOUT_mTheUnit.CHAN_BabyAlarm.name_ = C2_LightsOn;
			OUT_.BabyAlarm (CHNOUT_mTheUnit.CHAN_BabyAlarm.name_);
			break;
		case 5:  /* STATE Warning */
			status_PrimitiveBehavior.write_access_.STATE = 1;  /* STATE Alarm */
			CHNOUT_mTheUnit.CHAN_BabyAlarm.name_ = C2_SoundOn;
			OUT_.BabyAlarm (CHNOUT_mTheUnit.CHAN_BabyAlarm.name_);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Silent of INPORT Noise  ***/
	case C1_Silent:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case 1:  /* STATE Alarm */
			status_PrimitiveBehavior.write_access_.STATE = 5;  /* STATE Warning */
			CHNOUT_mTheUnit.CHAN_BabyAlarm.name_ = C2_SoundOff;
			OUT_.BabyAlarm (CHNOUT_mTheUnit.CHAN_BabyAlarm.name_);
			break;
		case 2:  /* STATE Info */
			status_PrimitiveBehavior.write_access_.STATE = 3;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_BabyAlarm.name_ = C2_LightsOff;
			OUT_.BabyAlarm (CHNOUT_mTheUnit.CHAN_BabyAlarm.name_);
			break;
		case 5:  /* STATE Warning */
			status_PrimitiveBehavior.write_access_.STATE = 2;  /* STATE Info */
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	return;
}

#undef EXCEPTION

/* Process Initialization Function */

void fINIT_PrimitiveBehavior (void)
{
	status_PrimitiveBehavior.write_access_.STATE = 3;  /* STATE On */
}

/*********************************************************************
	End of Module for PROCESS PrimitiveBehavior
*********************************************************************/
