
/*********************************************************************
	SYSTEM Lillebro
	Module for PROCESS Behavior
	Filename: Behavior.c
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

#define SELF status_Behavior.write_access_
#define STATUS status_Behavior.read_access_
#define TIME time_mDriveUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Avoid 1
#define Wander 2


/* INPULSES */
#define IP_WANDER 1
#define IP_AVOID 2


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
int fPULSE_IndicatorLight (unsigned char name_);

/* Global Declarations */

union tSTATUS_Behavior status_Behavior;

/* Function Prototypes */

int fPULSE_Behavior (unsigned char name_);
void fINIT_Behavior (void);

/* Input Channel Functions */

int fPULSE_Behavior (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE AVOID  ***/
	case O6_ATTENTION:		/***  PULSE CAST from PROCESS Proximity  ***/
	case O6_DANGER:
		switch (status_Behavior.read_access_.STATE)
		{
		case 2:  /* STATE Wander */
			status_Behavior.write_access_.STATE = 1;  /* STATE Avoid */
			fPULSE_IndicatorLight (O7_AVOID);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE WANDER  ***/
	case O6_CLEAR:		/***  PULSE CAST from PROCESS Proximity  ***/
		switch (status_Behavior.read_access_.STATE)
		{
		case 1:  /* STATE Avoid */
			status_Behavior.write_access_.STATE = 2;  /* STATE Wander */
			fPULSE_IndicatorLight (O7_WANDER);
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

void fINIT_Behavior (void)
{
	status_Behavior.write_access_.STATE = 2;  /* STATE Wander */
}

/*********************************************************************
	End of Module for PROCESS Behavior
*********************************************************************/