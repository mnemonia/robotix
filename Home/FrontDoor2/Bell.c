
/*********************************************************************
	SYSTEM FrontDoor
	Module for PROCESS Bell
	Filename: Bell.c
	generated by CIP Tool(R) Version 4.41.00
		November 10, 2013  9:40:45 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned int' for delays
		C-code
*********************************************************************/

/* Include Files */

#include "mArduinoUnit.h"

/* Process Macro Definitions */

#define SELF status_Bell.write_access_
#define STATUS status_Bell.read_access_
#define TIME time_mArduinoUnit

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

#define O3_OFF 4
#define O3_ON 3
#define O2_DOWN 1
#define O2_UP 2

/* External Declarations */

extern unsigned int time_mArduinoUnit;
extern union tCHNOUT_mArduinoUnit CHNOUT_mArduinoUnit;

void fUPDATE_Sonnerie (void);

/* Global Declarations */

union tSTATUS_Bell status_Bell;

/* Function Prototypes */

int fPULSE_Bell (unsigned char name_);
void fINIT_Bell (void);

/* Input Channel Functions */

int fPULSE_Bell (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE OFF  ***/
	case O3_OFF:		/***  PULSE CAST from PROCESS BellSwitch  ***/
		switch (status_Bell.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_Bell.write_access_.STATE = 1;  /* STATE Off */
			CHNOUT_mArduinoUnit.CHAN_BellOutChannel.name_ = C4_OFF;
			OUT_.BellOutChannel (CHNOUT_mArduinoUnit.CHAN_BellOutChannel.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE ON  ***/
	case O3_ON:		/***  PULSE CAST from PROCESS BellSwitch  ***/
		switch (status_Bell.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Bell.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mArduinoUnit.CHAN_BellOutChannel.name_ = C4_ON;
			OUT_.BellOutChannel (CHNOUT_mArduinoUnit.CHAN_BellOutChannel.name_);
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

void fINIT_Bell (void)
{
	status_Bell.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS Bell
*********************************************************************/