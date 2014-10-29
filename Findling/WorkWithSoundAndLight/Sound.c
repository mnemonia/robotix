
/*********************************************************************
	SYSTEM Findling01
	Module for PROCESS Sound
	Filename: Sound.c
	generated by CIP Tool(R) Version 4.41.00
		October 29, 2014  7:18:35 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Sound.write_access_
#define STATUS status_Sound.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Off 1
#define On 2



/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;


/* Global Declarations */

union tSTATUS_Sound status_Sound;

/* Function Prototypes */

void fICHAN_SoundLoudnessIn (unsigned char name_);
void fICHAN_SoundSwitchIn (unsigned char name_);
void fINIT_Sound (void);

/* Input Channel Functions */

void fICHAN_SoundLoudnessIn (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE MINUS of INPORT LoudnessIn  ***/
	case C8_MINUS:
		switch (status_Sound.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_Sound.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_SoundActionOut.name_ = C10_MINUS;
			OUT_.SoundActionOut (CHNOUT_mTheUnit.CHAN_SoundActionOut.name_);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE PLUS of INPORT LoudnessIn  ***/
	case C8_PLUS:
		switch (status_Sound.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Sound.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_SoundActionOut.name_ = C10_PLUS;
			OUT_.SoundActionOut (CHNOUT_mTheUnit.CHAN_SoundActionOut.name_);
			break;
		case 2:  /* STATE On */
			status_Sound.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_SoundActionOut.name_ = C10_PLUS;
			OUT_.SoundActionOut (CHNOUT_mTheUnit.CHAN_SoundActionOut.name_);
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

void fICHAN_SoundSwitchIn (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE TOGGLE of INPORT ToggleIn  ***/
	case C6_TOGGLE:
		switch (status_Sound.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Sound.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_SoundActionOut.name_ = C10_ON;
			OUT_.SoundActionOut (CHNOUT_mTheUnit.CHAN_SoundActionOut.name_);
			break;
		case 2:  /* STATE On */
			status_Sound.write_access_.STATE = 1;  /* STATE Off */
			CHNOUT_mTheUnit.CHAN_SoundActionOut.name_ = C10_OFF;
			OUT_.SoundActionOut (CHNOUT_mTheUnit.CHAN_SoundActionOut.name_);
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

void fINIT_Sound (void)
{
	status_Sound.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS Sound
*********************************************************************/
