
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS AmbientLight
	Filename: AmbientLight.c
	generated by CIP Tool(R) Version 4.41.00
		February 18, 2015  2:26:12 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define SELF status_AmbientLight.write_access_
#define STATUS status_AmbientLight.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Off 1
#define On 2


/* INPULSES */
#define IP_ON 1
#define IP_OFF 2


/* OUTPULSES */

#define O5_OFF 8
#define O5_ON 7
#define O8_IS_OFF 17
#define O8_IS_ON 18
#define O8_TURN_OFF 16
#define O8_TURN_OFF_STEP 14
#define O8_TURN_ON 15
#define O8_TURN_ON_STEP 13
#define O9_PRESS 20
#define O6_PRESS 9
#define O2_OFF 4
#define O2_ON 3

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

void fUPDATE_Lights (void);
int fPULSE_AmbientLightDimmer (unsigned char name_);

/* Global Declarations */

union tSTATUS_AmbientLight status_AmbientLight;

/* Function Prototypes */

int fPULSE_AmbientLight (unsigned char name_);
void fINIT_AmbientLight (void);

/* Input Channel Functions */

int fPULSE_AmbientLight (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE OFF  ***/
	case O8_IS_OFF:		/***  PULSE CAST from PROCESS LightController  ***/
	case O8_TURN_OFF:
		switch (status_AmbientLight.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_AmbientLight.write_access_.STATE = 1;  /* STATE Off */
			fPULSE_AmbientLightDimmer (O5_OFF);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE ON  ***/
	case O8_TURN_OFF_STEP:		/***  PULSE CAST from PROCESS LightController  ***/
	case O8_TURN_ON:
	case O8_TURN_ON_STEP:
		switch (status_AmbientLight.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_AmbientLight.write_access_.STATE = 2;  /* STATE On */
			fPULSE_AmbientLightDimmer (O5_ON);
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

void fINIT_AmbientLight (void)
{
	status_AmbientLight.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS AmbientLight
*********************************************************************/
