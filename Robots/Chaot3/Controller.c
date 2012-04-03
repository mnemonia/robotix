
/*********************************************************************
	SYSTEM Chaot
	Module for PROCESS Controller
	Filename: Controller.c
	generated by CIP Tool(R) Version 4.41.00
		April 3, 2012  2:01:11 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mChaotUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Controller.write_access_
#define STATUS status_Controller.read_access_
#define TIME time_mChaotUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Drawing1 1
#define Drawing2 2
#define Ready 3


/* INPULSES */
#define IP_DRAW 1


/* OUTPULSES */

#define O5_DONE 7
#define O3_SHAKE 1
#define O3_START 6
#define O2_INDICATING 5
#define O4_MEASURED 4
#define O1_DONE 3

/* External Declarations */

extern unsigned long time_mChaotUnit;
extern union tCHNOUT_mChaotUnit CHNOUT_mChaotUnit;

void fUPDATE_Robot (void);
int fPULSE_Shaker (unsigned char name_);
int fPULSE_Indicator (unsigned char name_);

/* Global Declarations */

union tSTATUS_Controller status_Controller;

/* Function Prototypes */

void fICHAN_Start (unsigned char name_);
int fPULSE_Controller (unsigned char name_);
void fINIT_Controller (void);

/* Input Channel Functions */

void fICHAN_Start (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE START of INPORT InCommands  ***/
	case C1_START:
		switch (status_Controller.read_access_.STATE)
		{
		case 3:  /* STATE Ready */
			status_Controller.write_access_.STATE = 1;  /* STATE Drawing1 */
			fPULSE_Shaker (O3_START);
			fPULSE_Indicator (O3_START);
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

int fPULSE_Controller (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE DRAW  ***/
	case O2_INDICATING:		/***  PULSE CAST from PROCESS Indicator  ***/
		switch (status_Controller.read_access_.STATE)
		{
		case 1:  /* STATE Drawing1 */
			status_Controller.write_access_.STATE = 2;  /* STATE Drawing2 */
			fPULSE_Shaker (O3_SHAKE);
			break;
		case 2:  /* STATE Drawing2 */
			status_Controller.write_access_.STATE = 3;  /* STATE Ready */
			CHNOUT_mChaotUnit.CHAN_ControllerActions.name_ = C6_DRAWED;
			OUT_.ControllerActions (CHNOUT_mChaotUnit.CHAN_ControllerActions.name_);
			fPULSE_Shaker (O3_SHAKE);
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

void fINIT_Controller (void)
{
	status_Controller.write_access_.STATE = 3;  /* STATE Ready */
}

/*********************************************************************
	End of Module for PROCESS Controller
*********************************************************************/
