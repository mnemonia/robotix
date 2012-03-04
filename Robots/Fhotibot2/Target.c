
/*********************************************************************
	SYSTEM Fhotibot2
	Module for PROCESS Target
	Filename: Target.c
	generated by CIP Tool(R) Version 4.41.00
		March 3, 2012  11:31:06 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Target.write_access_
#define STATUS status_Target.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define Ahead 1
#define Left 2
#define Right 3
#define Unknown 4



/* OUTPULSES */

#define O5_BWD_RIGHT 6
#define O5_FWD 7
#define O3_BWD 9
#define O3_BWD_RIGHT 11
#define O3_FWD 8
#define O3_LEFT 10
#define O2_AHEAD 3
#define O2_LEFT 1
#define O2_RIGHT 2
#define O2_UNKNOWN 4

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

void fUPDATE_Simple (void);
int fPULSE_Drive (unsigned char name_);

/* Global Declarations */

union tSTATUS_Target status_Target;

/* Function Prototypes */

void fICHAN_PositionInfo (unsigned char name_);
void fINIT_Target (void);

/* Input Channel Functions */

void fICHAN_PositionInfo (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE Ahead of INPORT Target  ***/
	case C1_Ahead:
		switch (status_Target.read_access_.STATE)
		{
		case 2:  /* STATE Left */
			status_Target.write_access_.STATE = 1;  /* STATE Ahead */
			fPULSE_Drive (O2_AHEAD);
			break;
		case 3:  /* STATE Right */
			status_Target.write_access_.STATE = 1;  /* STATE Ahead */
			fPULSE_Drive (O2_AHEAD);
			break;
		case 4:  /* STATE Unknown */
			status_Target.write_access_.STATE = 1;  /* STATE Ahead */
			fPULSE_Drive (O2_AHEAD);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Left of INPORT Target  ***/
	case C1_Left:
		switch (status_Target.read_access_.STATE)
		{
		case 1:  /* STATE Ahead */
			status_Target.write_access_.STATE = 2;  /* STATE Left */
			fPULSE_Drive (O2_LEFT);
			break;
		case 3:  /* STATE Right */
			status_Target.write_access_.STATE = 2;  /* STATE Left */
			fPULSE_Drive (O2_LEFT);
			break;
		case 4:  /* STATE Unknown */
			status_Target.write_access_.STATE = 2;  /* STATE Left */
			fPULSE_Drive (O2_LEFT);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Right of INPORT Target  ***/
	case C1_Right:
		switch (status_Target.read_access_.STATE)
		{
		case 1:  /* STATE Ahead */
			status_Target.write_access_.STATE = 3;  /* STATE Right */
			fPULSE_Drive (O2_RIGHT);
			break;
		case 2:  /* STATE Left */
			status_Target.write_access_.STATE = 3;  /* STATE Right */
			fPULSE_Drive (O2_RIGHT);
			break;
		case 4:  /* STATE Unknown */
			status_Target.write_access_.STATE = 3;  /* STATE Right */
			fPULSE_Drive (O2_RIGHT);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Unknown of INPORT Target  ***/
	case C1_Unknown:
		switch (status_Target.read_access_.STATE)
		{
		case 1:  /* STATE Ahead */
			status_Target.write_access_.STATE = 4;  /* STATE Unknown */
			fPULSE_Drive (O2_UNKNOWN);
			break;
		case 2:  /* STATE Left */
			status_Target.write_access_.STATE = 4;  /* STATE Unknown */
			fPULSE_Drive (O2_UNKNOWN);
			break;
		case 3:  /* STATE Right */
			status_Target.write_access_.STATE = 4;  /* STATE Unknown */
			fPULSE_Drive (O2_UNKNOWN);
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Simple ();
	return;
}

#undef EXCEPTION

/* Process Initialization Function */

void fINIT_Target (void)
{
	status_Target.write_access_.STATE = 4;  /* STATE Unknown */
}

/*********************************************************************
	End of Module for PROCESS Target
*********************************************************************/
