
/*********************************************************************
	SYSTEM Fhotibot
	Module for PROCESS DriveControl
	Filename: DriveControl.c
	generated by CIP Tool(R) Version 4.41.00
		February 4, 2012  10:35:39 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_DriveControl.write_access_
#define STATUS status_DriveControl.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define Backward 1
#define BackwardRight 2
#define Forward 3
#define Left 4
#define Stop 5



/* OUTPULSES */

#define O3_Backward 4
#define O3_BackwardRight 5
#define O3_Forward 1
#define O3_Left 3
#define O3_Stop 2

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

int fPULSE_TrackDrive (unsigned char name_);

/* Global Declarations */

union tSTATUS_DriveControl status_DriveControl;

/* Function Prototypes */

void fICHAN_Radar (unsigned char name_);
void fINIT_DriveControl (void);

/* Input Channel Functions */

void fICHAN_Radar (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE Attention of INPORT Obstacle  ***/
	case C3_Attention:
		switch (status_DriveControl.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_DriveControl.write_access_.STATE = 2;  /* STATE BackwardRight */
			fPULSE_TrackDrive (O3_BackwardRight);
			break;
		case 3:  /* STATE Forward */
			status_DriveControl.write_access_.STATE = 4;  /* STATE Left */
			fPULSE_TrackDrive (O3_Left);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Clear of INPORT Obstacle  ***/
	case C3_Clear:
		switch (status_DriveControl.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_DriveControl.write_access_.STATE = 3;  /* STATE Forward */
			fPULSE_TrackDrive (O3_BackwardRight);
			break;
		case 2:  /* STATE BackwardRight */
			status_DriveControl.write_access_.STATE = 3;  /* STATE Forward */
			fPULSE_TrackDrive (O3_Forward);
			break;
		case 4:  /* STATE Left */
			status_DriveControl.write_access_.STATE = 3;  /* STATE Forward */
			fPULSE_TrackDrive (O3_Forward);
			break;
		case 5:  /* STATE Stop */
			status_DriveControl.write_access_.STATE = 3;  /* STATE Forward */
			fPULSE_TrackDrive (O3_Forward);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE Danger of INPORT Obstacle  ***/
	case C3_Danger:
		switch (status_DriveControl.read_access_.STATE)
		{
		case 3:  /* STATE Forward */
			status_DriveControl.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_TrackDrive (O3_Backward);
			break;
		case 4:  /* STATE Left */
			status_DriveControl.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_TrackDrive (O3_Backward);
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

void fINIT_DriveControl (void)
{
	status_DriveControl.write_access_.STATE = 5;  /* STATE Stop */
}

/*********************************************************************
	End of Module for PROCESS DriveControl
*********************************************************************/