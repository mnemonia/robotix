
/*********************************************************************
	SYSTEM Fhotibot2
	Module for PROCESS Drive
	Filename: Drive.c
	generated by CIP Tool(R) Version 4.41.00
		March 3, 2012  9:58:37 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define SELF status_Drive.write_access_
#define STATUS status_Drive.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define Normal 1

/* STATES */
#define Run 1


/* INPULSES */
#define IP_FWD 1
#define IP_BWD 2
#define IP_RIGHT 3
#define IP_LEFT 4
#define IP_STOP 5
#define IP_BWD_RIGHT 6


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
	case O3_BWD:		/***  PULSE CAST from PROCESS ObjectAvoidance  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_BWD;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_BWD;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE BWD_RIGHT  ***/
	case O5_BWD_RIGHT:		/***  PULSE CAST from PROCESS Bump  ***/
	case O3_BWD_RIGHT:		/***  PULSE CAST from PROCESS ObjectAvoidance  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_BWD;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_STOP;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE FWD  ***/
	case O5_FWD:		/***  PULSE CAST from PROCESS Bump  ***/
	case O3_FWD:		/***  PULSE CAST from PROCESS ObjectAvoidance  ***/
	case O2_AHEAD:		/***  PULSE CAST from PROCESS Target  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_FWD;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_FWD;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE LEFT  ***/
	case O3_LEFT:		/***  PULSE CAST from PROCESS ObjectAvoidance  ***/
	case O2_LEFT:		/***  PULSE CAST from PROCESS Target  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_BWD;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_FWD;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE RIGHT  ***/
	case O2_RIGHT:		/***  PULSE CAST from PROCESS Target  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_FWD;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_BWD;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE STOP  ***/
	case O2_UNKNOWN:		/***  PULSE CAST from PROCESS Target  ***/
		switch (status_Drive.read_access_.STATE)
		{
		case 1:  /* STATE Run */
			status_Drive.write_access_.STATE = 1;  /* STATE Run */
			CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_ = C2_STOP;
			OUT_.MotorLeftActions (CHNOUT_mTheUnit.CHAN_MotorLeftActions.name_);
			CHNOUT_mTheUnit.CHAN_MotorRightActions.name_ = C3_STOP;
			OUT_.MotorRightActions (CHNOUT_mTheUnit.CHAN_MotorRightActions.name_);
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
	status_Drive.write_access_.STATE = 1;  /* STATE Run */
}

/*********************************************************************
	End of Module for PROCESS Drive
*********************************************************************/
