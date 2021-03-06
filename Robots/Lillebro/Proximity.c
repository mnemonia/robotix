
/*********************************************************************
	SYSTEM Lillebro
	Module for PROCESS Proximity
	Filename: Proximity.c
	generated by CIP Tool(R) Version 4.41.00
		January 4, 2015  4:10:34 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned char' for delays
		C-code
*********************************************************************/

/* Include Files */

#include "mDriveUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_Proximity.write_access_
#define STATUS status_Proximity.read_access_
#define TIME time_mDriveUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Attention 1
#define Clear 2
#define Danger 3



/* OUTPULSES */

#define O7_AVOID 16
#define O7_WANDER 17
#define O5_GO_BACKWARD 8
#define O5_GO_STRAIGHT 7
#define O5_STOP 9
#define O5_TURN_LEFT 5
#define O5_TURN_RIGHT 6
#define O3_BWD 10
#define O3_FWD 3
#define O3_STOP 4
#define O3_TURN_LEFT 2
#define O3_TURN_RIGHT 1
#define O8_SHOW_AVOID 14
#define O8_SHOW_WANDER 15
#define O6_ATTENTION 11
#define O6_CLEAR 13
#define O6_DANGER 12

/* External Declarations */

extern unsigned char time_mDriveUnit;
extern union tCHNOUT_mDriveUnit CHNOUT_mDriveUnit;

void fUPDATE_Controller (void);
int fPULSE_Drive (unsigned char name_);
int fPULSE_Behavior (unsigned char name_);

/* Global Declarations */

union tSTATUS_Proximity status_Proximity;

/* Function Prototypes */

void fICHAN_ProximityEvents (unsigned char name_);
void fINIT_Proximity (void);

/* Input Channel Functions */

void fICHAN_ProximityEvents (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE ATTENTION of INPORT ProximityInport  ***/
	case C4_ATTENTION:
		switch (status_Proximity.read_access_.STATE)
		{
		case 2:  /* STATE Clear */
			status_Proximity.write_access_.STATE = 1;  /* STATE Attention */
			fPULSE_Drive (O6_ATTENTION);
			fPULSE_Behavior (O6_ATTENTION);
			break;
		case 3:  /* STATE Danger */
			status_Proximity.write_access_.STATE = 1;  /* STATE Attention */
			fPULSE_Drive (O6_ATTENTION);
			fPULSE_Behavior (O6_ATTENTION);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE CLEAR of INPORT ProximityInport  ***/
	case C4_CLEAR:
		switch (status_Proximity.read_access_.STATE)
		{
		case 1:  /* STATE Attention */
			status_Proximity.write_access_.STATE = 2;  /* STATE Clear */
			fPULSE_Drive (O6_CLEAR);
			fPULSE_Behavior (O6_CLEAR);
			break;
		case 3:  /* STATE Danger */
			status_Proximity.write_access_.STATE = 2;  /* STATE Clear */
			fPULSE_Drive (O6_CLEAR);
			fPULSE_Behavior (O6_CLEAR);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE DANGER of INPORT ProximityInport  ***/
	case C4_DANGER:
		switch (status_Proximity.read_access_.STATE)
		{
		case 1:  /* STATE Attention */
			status_Proximity.write_access_.STATE = 3;  /* STATE Danger */
			fPULSE_Drive (O6_DANGER);
			fPULSE_Behavior (O6_DANGER);
			break;
		case 2:  /* STATE Clear */
			status_Proximity.write_access_.STATE = 3;  /* STATE Danger */
			fPULSE_Drive (O6_DANGER);
			fPULSE_Behavior (O6_DANGER);
			break;
		default: 
			return;
		}
		break;
	default: 
		return;
	}
	fUPDATE_Controller ();
	return;
}

#undef EXCEPTION

/* Process Initialization Function */

void fINIT_Proximity (void)
{
	status_Proximity.write_access_.STATE = 2;  /* STATE Clear */
}

/*********************************************************************
	End of Module for PROCESS Proximity
*********************************************************************/
