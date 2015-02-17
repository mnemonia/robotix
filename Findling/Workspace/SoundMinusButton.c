
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS SoundMinusButton
	Filename: SoundMinusButton.c
	generated by CIP Tool(R) Version 4.41.00
		February 17, 2015  10:23:02 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_SoundMinusButton.write_access_
#define STATUS status_SoundMinusButton.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Idle 1
#define Pressed 2



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
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

void fUPDATE_Sound (void);
int fPULSE_SoundController (unsigned char name_);

/* Global Declarations */

union tSTATUS_SoundMinusButton status_SoundMinusButton;

/* Function Prototypes */

void fICHAN_SoundMinusChannel (unsigned char name_);
void fINIT_SoundMinusButton (void);

/* Input Channel Functions */

void fICHAN_SoundMinusChannel (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE PRESSED of INPORT SoundMinusInport  ***/
	case C9_PRESSED:
		switch (status_SoundMinusButton.read_access_.STATE)
		{
		case 1:  /* STATE Idle */
			status_SoundMinusButton.write_access_.STATE = 2;  /* STATE Pressed */
			fPULSE_SoundController (O12_PRESSED);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE RELEASED of INPORT SoundMinusInport  ***/
	case C9_RELEASED:
		switch (status_SoundMinusButton.read_access_.STATE)
		{
		case 2:  /* STATE Pressed */
			status_SoundMinusButton.write_access_.STATE = 1;  /* STATE Idle */
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

/* Process Initialization Function */

void fINIT_SoundMinusButton (void)
{
	status_SoundMinusButton.write_access_.STATE = 1;  /* STATE Idle */
}

/*********************************************************************
	End of Module for PROCESS SoundMinusButton
*********************************************************************/
