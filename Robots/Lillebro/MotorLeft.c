
/*********************************************************************
	SYSTEM Lillebro
	Module for PROCESS MotorLeft
	Filename: MotorLeft.c
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

#define SELF status_MotorLeft.write_access_
#define STATUS status_MotorLeft.read_access_
#define TIME time_mDriveUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Backward 1
#define Forward 2
#define Stop 3


/* INPULSES */
#define IP_STOP 1
#define IP_FWD 2
#define IP_BWD 3


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

/* Global Declarations */

union tSTATUS_MotorLeft status_MotorLeft;

/* Function Prototypes */

int fPULSE_MotorLeft (unsigned char name_);
void fINIT_MotorLeft (void);

/* Input Channel Functions */

int fPULSE_MotorLeft (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE BWD  ***/
	case O3_BWD:		/***  PULSE CAST from PROCESS Drive  ***/
	case O3_TURN_LEFT:
		switch (status_MotorLeft.read_access_.STATE)
		{
		case 2:  /* STATE Forward */
			status_MotorLeft.write_access_.STATE = 1;  /* STATE Backward */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_BWD;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
			break;
		case 3:  /* STATE Stop */
			status_MotorLeft.write_access_.STATE = 1;  /* STATE Backward */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_BWD;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FWD  ***/
	case O3_FWD:		/***  PULSE CAST from PROCESS Drive  ***/
	case O3_TURN_RIGHT:
		switch (status_MotorLeft.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_MotorLeft.write_access_.STATE = 2;  /* STATE Forward */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_FWD;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
			break;
		case 3:  /* STATE Stop */
			status_MotorLeft.write_access_.STATE = 2;  /* STATE Forward */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_FWD;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE STOP  ***/
	case O3_STOP:		/***  PULSE CAST from PROCESS Drive  ***/
		switch (status_MotorLeft.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_MotorLeft.write_access_.STATE = 3;  /* STATE Stop */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_STOP;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
			break;
		case 2:  /* STATE Forward */
			status_MotorLeft.write_access_.STATE = 3;  /* STATE Stop */
			CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_ = C2_STOP;
			OUT_.LeftMotorActions (CHNOUT_mDriveUnit.CHAN_LeftMotorActions.name_);
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

void fINIT_MotorLeft (void)
{
	status_MotorLeft.write_access_.STATE = 3;  /* STATE Stop */
}

/*********************************************************************
	End of Module for PROCESS MotorLeft
*********************************************************************/
