
/*********************************************************************
	SYSTEM Fhotibot
	Module for PROCESS DriveObserver
	Filename: DriveObserver.c
	generated by CIP Tool(R) Version 4.41.00
		February 15, 2012  12:14:05 am
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define SELF status_DriveObserver.write_access_
#define STATUS status_DriveObserver.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define AvoidingObstacle 1
#define ClearOfObstacle 2



/* OUTPULSES */

#define O15_AvoidingObstacle 5
#define O15_ClearOfObstacle 6
#define O7_Ahead 1
#define O7_Behind 2
#define O7_ToTheLeft 4
#define O7_ToTheRight 3
#define O7_Unknown 7

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

int fPULSE_Finder (unsigned char name_);

/* Global Declarations */

union tSTATUS_DriveObserver status_DriveObserver;

/* Function Prototypes */

void fICHAN_ObstacleEvents (unsigned char name_);
void fINIT_DriveObserver (void);

/* Input Channel Functions */

void fICHAN_ObstacleEvents (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE AvoidingObstacle of INPORT ObstacleAvoidanceEvent  ***/
	case C9_AvoidingObstacle:
		switch (status_DriveObserver.read_access_.STATE)
		{
		case 2:  /* STATE ClearOfObstacle */
			status_DriveObserver.write_access_.STATE = 1;  /* STATE AvoidingObstacle */
			fPULSE_Finder (O15_AvoidingObstacle);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE ClearOfObstacles of INPORT ObstacleAvoidanceEvent  ***/
	case C9_ClearOfObstacles:
		switch (status_DriveObserver.read_access_.STATE)
		{
		case 1:  /* STATE AvoidingObstacle */
			status_DriveObserver.write_access_.STATE = 2;  /* STATE ClearOfObstacle */
			fPULSE_Finder (O15_ClearOfObstacle);
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

void fINIT_DriveObserver (void)
{
	status_DriveObserver.write_access_.STATE = 2;  /* STATE ClearOfObstacle */
}

/*********************************************************************
	End of Module for PROCESS DriveObserver
*********************************************************************/
