
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS LightMinusButton
	Filename: LightMinusButton.c
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
#define SELF status_LightMinusButton.write_access_
#define STATUS status_LightMinusButton.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Idle 1
#define Pressed 2



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

union tSTATUS_LightMinusButton status_LightMinusButton;

/* Function Prototypes */

void fICHAN_LightDimMinusEvents (unsigned char name_);
void fINIT_LightMinusButton (void);

/* Input Channel Functions */

void fICHAN_LightDimMinusEvents (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE PRESS of INPORT LightMinusButtonEvents  ***/
	case C7_PRESS:
		switch (status_LightMinusButton.read_access_.STATE)
		{
		case 1:  /* STATE Idle */
			status_LightMinusButton.write_access_.STATE = 2;  /* STATE Pressed */
			fPULSE_LightController (O9_PRESS);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE RELEASE of INPORT LightMinusButtonEvents  ***/
	case C7_RELEASE:
		switch (status_LightMinusButton.read_access_.STATE)
		{
		case 2:  /* STATE Pressed */
			status_LightMinusButton.write_access_.STATE = 1;  /* STATE Idle */
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

/* Process Initialization Function */

void fINIT_LightMinusButton (void)
{
	status_LightMinusButton.write_access_.STATE = 1;  /* STATE Idle */
}

/*********************************************************************
	End of Module for PROCESS LightMinusButton
*********************************************************************/
