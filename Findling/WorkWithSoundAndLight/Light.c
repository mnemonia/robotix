
/*********************************************************************
	SYSTEM Findling01
	Module for PROCESS Light
	Filename: Light.c
	generated by CIP Tool(R) Version 4.41.00
		December 11, 2014  5:32:34 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Light.write_access_
#define STATUS status_Light.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Off 1
#define On 2



/* OUTPULSES */

#define O1_OFF 2
#define O1_ON 1

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

int fPULSE_Ambient (unsigned char name_);

/* Global Declarations */

union tSTATUS_Light status_Light;

/* Function Prototypes */

void fICHAN_LightSwitchIn (unsigned char name_);
void fICHAN_LightBrightnessIn (unsigned char name_);
void fINIT_Light (void);

/* Input Channel Functions */

void fICHAN_LightSwitchIn (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE TOGGLE of INPORT LightSwitch  ***/
	case C5_TOGGLE:
		switch (status_Light.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Light.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_LightActionOut.name_ = C9_ON;
			OUT_.LightActionOut (CHNOUT_mTheUnit.CHAN_LightActionOut.name_);
			fPULSE_Ambient (O1_ON);
			break;
		case 2:  /* STATE On */
			status_Light.write_access_.STATE = 1;  /* STATE Off */
			CHNOUT_mTheUnit.CHAN_LightActionOut.name_ = C9_OFF;
			OUT_.LightActionOut (CHNOUT_mTheUnit.CHAN_LightActionOut.name_);
			fPULSE_Ambient (O1_OFF);
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

void fICHAN_LightBrightnessIn (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE MINUS of INPORT LightBrightness  ***/
	case C7_MINUS:
		switch (status_Light.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_Light.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_LightActionOut.name_ = C9_MINUS;
			OUT_.LightActionOut (CHNOUT_mTheUnit.CHAN_LightActionOut.name_);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE PLUS of INPORT LightBrightness  ***/
	case C7_PLUS:
		switch (status_Light.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Light.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_LightActionOut.name_ = C9_PLUS;
			OUT_.LightActionOut (CHNOUT_mTheUnit.CHAN_LightActionOut.name_);
			fPULSE_Ambient (O1_ON);
			break;
		case 2:  /* STATE On */
			status_Light.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mTheUnit.CHAN_LightActionOut.name_ = C9_PLUS;
			OUT_.LightActionOut (CHNOUT_mTheUnit.CHAN_LightActionOut.name_);
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

void fINIT_Light (void)
{
	status_Light.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS Light
*********************************************************************/
