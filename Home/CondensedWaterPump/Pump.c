
/*********************************************************************
	SYSTEM CondensedWaterPump
	Module for PROCESS Pump
	Filename: Pump.c
	generated by CIP Tool(R) Version 4.41.00
		December 18, 2012  8:00:09 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mCondensedWaterPumpUnit.h"

/* Process Macro Definitions */

#define SELF status_Pump.write_access_
#define STATUS status_Pump.read_access_
#define TIME time_mCondensedWaterPumpUnit

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

#define O4_NO_WATER_DETECTED 4
#define O1_START 1
#define O1_STOP 2
#define O3_WATER_DETECTED 3

/* External Declarations */

extern unsigned long time_mCondensedWaterPumpUnit;
extern union tCHNOUT_mCondensedWaterPumpUnit CHNOUT_mCondensedWaterPumpUnit;


/* Global Declarations */

union tSTATUS_Pump status_Pump;

/* Function Prototypes */

int fPULSE_Pump (unsigned char name_);
void fINIT_Pump (void);

/* Input Channel Functions */

int fPULSE_Pump (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE OFF  ***/
	case O1_STOP:		/***  PULSE CAST from PROCESS ThreeStepController  ***/
		switch (status_Pump.read_access_.STATE)
		{
		case 2:  /* STATE On */
			status_Pump.write_access_.STATE = 1;  /* STATE Off */
			CHNOUT_mCondensedWaterPumpUnit.CHAN_PumpOutChannel.name_ = C2_OFF;
			OUT_.PumpOutChannel (CHNOUT_mCondensedWaterPumpUnit.CHAN_PumpOutChannel.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE ON  ***/
	case O1_START:		/***  PULSE CAST from PROCESS ThreeStepController  ***/
		switch (status_Pump.read_access_.STATE)
		{
		case 1:  /* STATE Off */
			status_Pump.write_access_.STATE = 2;  /* STATE On */
			CHNOUT_mCondensedWaterPumpUnit.CHAN_PumpOutChannel.name_ = C2_ON;
			OUT_.PumpOutChannel (CHNOUT_mCondensedWaterPumpUnit.CHAN_PumpOutChannel.name_);
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

void fINIT_Pump (void)
{
	status_Pump.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS Pump
*********************************************************************/