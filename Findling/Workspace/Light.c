
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS Light
	Filename: Light.c
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

#define SELF status_Light.write_access_
#define STATUS status_Light.read_access_
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

/* Global Declarations */

union tSTATUS_Light status_Light;

/* Function Prototypes */

int fPULSE_Light (unsigned char name_);
void fINIT_Light (void);

/* Input Channel Functions */

int fPULSE_Light (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE OFF  ***/
	case O8_IS_OFF:		/***  PULSE CAST from PROCESS LightController  ***/
		switch (status_Light.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_Light.write_access_.STATE = 1;  /* STATE Off */
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE ON  ***/
	case O8_TURN_OFF:		/***  PULSE CAST from PROCESS LightController  ***/
	case O8_TURN_OFF_STEP:
	case O8_TURN_ON:
	case O8_TURN_ON_STEP:
		switch (status_Light.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Light.write_access_.STATE = 2;  /* STATE On */
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

void fINIT_Light (void)
{
	status_Light.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS Light
*********************************************************************/
