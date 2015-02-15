
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS LightSwitch
	Filename: LightSwitch.c
	generated by CIP Tool(R) Version 4.41.00
		February 15, 2015  10:53:57 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_LightSwitch.write_access_
#define STATUS status_LightSwitch.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Off 1
#define On 2
#define TurningOff 3
#define TurningOn 4


/* INPULSES */
#define IP_IS_ON 1
#define IP_IS_OFF 2


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
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

void fUPDATE_Lights (void);
int fPULSE_LightController (unsigned char name_);

/* Global Declarations */

union tSTATUS_LightSwitch status_LightSwitch;

/* Function Prototypes */

void fICHAN_LightSwitchEvent (unsigned char name_);
int fPULSE_LightSwitch (unsigned char name_);
void fINIT_LightSwitch (void);

/* Input Channel Functions */

void fICHAN_LightSwitchEvent (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE TOGGLE of INPORT LightSwitchIn  ***/
	case C2_TOGGLE:
		switch (status_LightSwitch.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_LightSwitch.write_access_.STATE = 4;  /* STATE TurningOn */
			fPULSE_LightController (O2_ON);
			break;
		case 2:  /* STATE On */
			status_LightSwitch.write_access_.STATE = 3;  /* STATE TurningOff */
			fPULSE_LightController (O2_OFF);
			break;
		case 3:  /* STATE TurningOff */
			status_LightSwitch.write_access_.STATE = 4;  /* STATE TurningOn */
			fPULSE_LightController (O2_ON);
			break;
		case 4:  /* STATE TurningOn */
			status_LightSwitch.write_access_.STATE = 3;  /* STATE TurningOff */
			fPULSE_LightController (O2_OFF);
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

int fPULSE_LightSwitch (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE IS_OFF  ***/
	case O8_IS_OFF:		/***  PULSE CAST from PROCESS LightController  ***/
		switch (status_LightSwitch.read_access_.STATE)
		{
		case 3:  /* STATE TurningOff */
			status_LightSwitch.write_access_.STATE = 1;  /* STATE Off */
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE IS_ON  ***/
	case O8_IS_ON:		/***  PULSE CAST from PROCESS LightController  ***/
		switch (status_LightSwitch.read_access_.STATE)
		{
		case 4:  /* STATE TurningOn */
			status_LightSwitch.write_access_.STATE = 2;  /* STATE On */
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

/* Process Initialization Function */

void fINIT_LightSwitch (void)
{
	status_LightSwitch.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS LightSwitch
*********************************************************************/
