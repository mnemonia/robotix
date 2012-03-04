
/*********************************************************************
	SYSTEM Fhotibot2
	Module for PROCESS ObjectAvoidance
	Filename: ObjectAvoidance.c
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
#define SELF status_ObjectAvoidance.write_access_
#define STATUS status_ObjectAvoidance.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define Attention 1
#define AttentionAfterDanger 2
#define Clear 3
#define Danger 4



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

union tSTATUS_ObjectAvoidance status_ObjectAvoidance;

/* Function Prototypes */

void fICHAN_ObjectAvoidanceInfo (unsigned char name_);
void fINIT_ObjectAvoidance (void);

/* Input Channel Functions */

void fICHAN_ObjectAvoidanceInfo (unsigned char name_)
{
	switch (name_)
	{
		/***  MESSAGE ATTENTION of INPORT ObstacleInfo  ***/
	case C5_ATTENTION:
		switch (status_ObjectAvoidance.read_access_.STATE)
		{
		case 3:  /* STATE Clear */
			status_ObjectAvoidance.write_access_.STATE = 1;  /* STATE Attention */
			fPULSE_Drive (O3_LEFT);
			break;
		case 4:  /* STATE Danger */
			status_ObjectAvoidance.write_access_.STATE = 2;  /* STATE AttentionAfterDanger */
			fPULSE_Drive (O3_BWD_RIGHT);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE CLEAR of INPORT ObstacleInfo  ***/
	case C5_CLEAR:
		switch (status_ObjectAvoidance.read_access_.STATE)
		{
		case 1:  /* STATE Attention */
			status_ObjectAvoidance.write_access_.STATE = 3;  /* STATE Clear */
			fPULSE_Drive (O3_FWD);
			break;
		case 2:  /* STATE AttentionAfterDanger */
			status_ObjectAvoidance.write_access_.STATE = 3;  /* STATE Clear */
			fPULSE_Drive (O3_FWD);
			break;
		case 4:  /* STATE Danger */
			status_ObjectAvoidance.write_access_.STATE = 3;  /* STATE Clear */
			fPULSE_Drive (O3_FWD);
			break;
		default: 
			return;
		}
		break;
		/***  MESSAGE DANGER of INPORT ObstacleInfo  ***/
	case C5_DANGER:
		switch (status_ObjectAvoidance.read_access_.STATE)
		{
		case 1:  /* STATE Attention */
			status_ObjectAvoidance.write_access_.STATE = 4;  /* STATE Danger */
			fPULSE_Drive (O3_BWD);
			break;
		case 3:  /* STATE Clear */
			status_ObjectAvoidance.write_access_.STATE = 4;  /* STATE Danger */
			fPULSE_Drive (O3_BWD);
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

void fINIT_ObjectAvoidance (void)
{
	status_ObjectAvoidance.write_access_.STATE = 3;  /* STATE Clear */
}

/*********************************************************************
	End of Module for PROCESS ObjectAvoidance
*********************************************************************/
