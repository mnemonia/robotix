
/*********************************************************************
	SYSTEM Lillebro
	Module for PROCESS Drive
	Filename: Drive.c
	generated by CIP Tool(R) Version 4.41.00
		January 4, 2015  3:20:27 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned char' for delays
		C-code
*********************************************************************/

/* Include Files */

#include "mDriveUnit.h"

/* Process Macro Definitions */

#define SELF status_Drive.write_access_
#define STATUS status_Drive.read_access_
#define TIME time_mDriveUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Backward 1
#define Forward 2
#define Stop 3
#define TurnLeft 4
#define TurnRight 5


/* INPULSES */
#define IP_LEFT 1
#define IP_RIGHT 2
#define IP_FWD 3
#define IP_BWD 4
#define IP_STOP 5


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
int fPULSE_MotorLeft (unsigned char name_);
int fPULSE_MotorRight (unsigned char name_);

/* Global Declarations */

union tSTATUS_Drive status_Drive;

/* Function Prototypes */

int fPULSE_Drive (unsigned char name_);
void fINIT_Drive (void);

/* Input Channel Functions */

int fPULSE_Drive (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE BWD  ***/
	case O5_GO_BACKWARD:		/***  PULSE CAST from PROCESS Demo  ***/
	case O6_DANGER:		/***  PULSE CAST from PROCESS Proximity  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 2:  /* STATE Forward */
			status_Drive.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_MotorLeft (O3_BWD);
			fPULSE_MotorRight (O3_BWD);
			break;
		case 3:  /* STATE Stop */
			status_Drive.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_MotorLeft (O3_BWD);
			fPULSE_MotorRight (O3_BWD);
			break;
		case 4:  /* STATE TurnLeft */
			status_Drive.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_MotorLeft (O3_BWD);
			fPULSE_MotorRight (O3_BWD);
			break;
		case 5:  /* STATE TurnRight */
			status_Drive.write_access_.STATE = 1;  /* STATE Backward */
			fPULSE_MotorLeft (O3_BWD);
			fPULSE_MotorRight (O3_BWD);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FWD  ***/
	case O5_GO_STRAIGHT:		/***  PULSE CAST from PROCESS Demo  ***/
	case O6_CLEAR:		/***  PULSE CAST from PROCESS Proximity  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_Drive.write_access_.STATE = 2;  /* STATE Forward */
			fPULSE_MotorLeft (O3_FWD);
			fPULSE_MotorRight (O3_FWD);
			break;
		case 3:  /* STATE Stop */
			status_Drive.write_access_.STATE = 2;  /* STATE Forward */
			fPULSE_MotorLeft (O3_FWD);
			fPULSE_MotorRight (O3_FWD);
			break;
		case 4:  /* STATE TurnLeft */
			status_Drive.write_access_.STATE = 2;  /* STATE Forward */
			fPULSE_MotorLeft (O3_FWD);
			fPULSE_MotorRight (O3_FWD);
			break;
		case 5:  /* STATE TurnRight */
			status_Drive.write_access_.STATE = 2;  /* STATE Forward */
			fPULSE_MotorLeft (O3_FWD);
			fPULSE_MotorRight (O3_FWD);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE LEFT  ***/
	case O5_TURN_LEFT:		/***  PULSE CAST from PROCESS Demo  ***/
	case O6_ATTENTION:		/***  PULSE CAST from PROCESS Proximity  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_Drive.write_access_.STATE = 4;  /* STATE TurnLeft */
			fPULSE_MotorLeft (O3_TURN_LEFT);
			fPULSE_MotorRight (O3_TURN_LEFT);
			break;
		case 2:  /* STATE Forward */
			status_Drive.write_access_.STATE = 4;  /* STATE TurnLeft */
			fPULSE_MotorLeft (O3_TURN_LEFT);
			fPULSE_MotorRight (O3_TURN_LEFT);
			break;
		case 3:  /* STATE Stop */
			status_Drive.write_access_.STATE = 4;  /* STATE TurnLeft */
			fPULSE_MotorLeft (O3_TURN_LEFT);
			fPULSE_MotorRight (O3_TURN_LEFT);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE RIGHT  ***/
	case O5_TURN_RIGHT:		/***  PULSE CAST from PROCESS Demo  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_Drive.write_access_.STATE = 5;  /* STATE TurnRight */
			fPULSE_MotorLeft (O3_TURN_RIGHT);
			fPULSE_MotorRight (O3_TURN_RIGHT);
			break;
		case 2:  /* STATE Forward */
			status_Drive.write_access_.STATE = 5;  /* STATE TurnRight */
			fPULSE_MotorLeft (O3_TURN_RIGHT);
			fPULSE_MotorRight (O3_TURN_RIGHT);
			break;
		case 3:  /* STATE Stop */
			status_Drive.write_access_.STATE = 5;  /* STATE TurnRight */
			fPULSE_MotorLeft (O3_TURN_RIGHT);
			fPULSE_MotorRight (O3_TURN_RIGHT);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE STOP  ***/
	case O5_STOP:		/***  PULSE CAST from PROCESS Demo  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Backward */
			status_Drive.write_access_.STATE = 3;  /* STATE Stop */
			fPULSE_MotorLeft (O3_STOP);
			fPULSE_MotorRight (O3_STOP);
			break;
		case 2:  /* STATE Forward */
			status_Drive.write_access_.STATE = 3;  /* STATE Stop */
			fPULSE_MotorLeft (O3_STOP);
			fPULSE_MotorRight (O3_STOP);
			break;
		case 4:  /* STATE TurnLeft */
			status_Drive.write_access_.STATE = 3;  /* STATE Stop */
			fPULSE_MotorLeft (O3_STOP);
			fPULSE_MotorRight (O3_STOP);
			break;
		case 5:  /* STATE TurnRight */
			status_Drive.write_access_.STATE = 3;  /* STATE Stop */
			fPULSE_MotorLeft (O3_STOP);
			fPULSE_MotorRight (O3_STOP);
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

void fINIT_Drive (void)
{
	status_Drive.write_access_.STATE = 3;  /* STATE Stop */
}

/*********************************************************************
	End of Module for PROCESS Drive
*********************************************************************/
