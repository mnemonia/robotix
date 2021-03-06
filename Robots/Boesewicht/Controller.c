
/*********************************************************************
	SYSTEM Boesewicht
	Module for PROCESS Controller
	Filename: Controller.c
	generated by CIP Tool(R) Version 4.41.00
		September 19, 2012  12:35:52 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mBoesewicht.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Controller.write_access_
#define STATUS status_Controller.read_access_
#define TIME time_mBoesewicht

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define On 1



/* OUTPULSES */

#define O7_PLAY 8
#define O7_WAIT 9
#define O7_WAKEUP 7
#define O4_OPEN_EYES 4
#define O4_PLAY 5
#define O4_WAVE 3
#define O3_DOWN 2
#define O3_NEUTRAL 6
#define O3_UP 1
#define O8_Still 10

/* External Declarations */

extern unsigned long time_mBoesewicht;
extern union tCHNOUT_mBoesewicht CHNOUT_mBoesewicht;

void fUPDATE_Robot (void);
int fPULSE_Mouth (unsigned char name_);
int fPULSE_Eyes (unsigned char name_);
int fPULSE_WaveWings (unsigned char name_);

/* Global Declarations */

union tSTATUS_Controller status_Controller;

/* Function Prototypes */

void fICHAN_ControllerChannel (unsigned char name_);
void fINIT_Controller (void);

/* Input Channel Functions */

void fICHAN_ControllerChannel (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE ATTENTION of INPORT ControllerEvents  ***/
	case C6_ATTENTION:
		switch (status_Controller.read_access_.STATE)
		{
		case 1:  /* STATE On */
			status_Controller.write_access_.STATE = 1;  /* STATE On */
			fPULSE_Mouth (O7_WAKEUP);
			fPULSE_Eyes (O7_WAKEUP);
			fPULSE_WaveWings (O7_WAKEUP);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE CLEAR of INPORT ControllerEvents  ***/
	case C6_CLEAR:
		switch (status_Controller.read_access_.STATE)
		{
		case 1:  /* STATE On */
			status_Controller.write_access_.STATE = 1;  /* STATE On */
			fPULSE_Mouth (O7_WAIT);
			fPULSE_Eyes (O7_WAIT);
			fPULSE_WaveWings (O7_WAIT);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE DANGER of INPORT ControllerEvents  ***/
	case C6_DANGER:
		switch (status_Controller.read_access_.STATE)
		{
		case 1:  /* STATE On */
			status_Controller.write_access_.STATE = 1;  /* STATE On */
			fPULSE_Mouth (O7_PLAY);
			fPULSE_Eyes (O7_PLAY);
			fPULSE_WaveWings (O7_PLAY);
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Robot ();
	return;
}

#undef EXCEPTION

/* Process Initialization Function */

void fINIT_Controller (void)
{
	status_Controller.write_access_.STATE = 1;  /* STATE On */
}

/*********************************************************************
	End of Module for PROCESS Controller
*********************************************************************/
