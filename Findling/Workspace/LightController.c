
/*********************************************************************
	SYSTEM Workspace
	Module for PROCESS LightController
	Filename: LightController.c
	generated by CIP Tool(R) Version 4.41.00
		February 15, 2015  8:35:01 pm
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* Process Macro Definitions */

#define SELF status_LightController.write_access_
#define STATUS status_LightController.read_access_
#define TIME time_mTheUnit

/* Process Definitions */

/* MODES */
#define manual 1
#define automatic 2

/* STATES */
#define Off 1
#define On 2
#define TurningOff 3
#define TurningOn 4


/* INPULSES */
#define IP_TURN_ON_STEP 1
#define IP_TURN_OFF_STEP 2
#define IP_TURN_ON 3
#define IP_TURN_OFF 4
#define IP_IS_ON 5
#define IP_IS_OFF 6


/* OUTPULSES */

#define O5_OFF 8
#define O5_ON 7
#define O3_OFF 2
#define O3_ON 1
#define O8_IS_OFF 17
#define O8_IS_ON 18
#define O8_TURN_OFF 16
#define O8_TURN_OFF_STEP 14
#define O8_TURN_ON 15
#define O8_TURN_ON_STEP 13
#define O1_IS_OFF 6
#define O1_IS_ON 5
#define O9_PRESS 20
#define O6_PRESS 9
#define O2_OFF 4
#define O2_ON 3

/* External Declarations */

extern unsigned long time_mTheUnit;
extern union tCHNOUT_mTheUnit CHNOUT_mTheUnit;
extern union tSTATUS_LightMinusButton status_LightMinusButton;
extern union tSTATUS_LightPlusButton status_LightPlusButton;
extern union tSTATUS_LightSwitch status_LightSwitch;

void fUPDATE_Controller (void);
int fPULSE_AmbientLight (unsigned char name_);
int fPULSE_Light (unsigned char name_);
int fPULSE_LightDimmer (unsigned char name_);
int fPULSE_LightSwitch (unsigned char name_);

/* Global Declarations */

union tSTATUS_LightController status_LightController;
const unsigned char MODTAB_LightController[2][2][4] =       /*  [LightMinusButton states] [LightPlusButton states] [LightSwitch states] */
	{{{2, 2, 2, 2}, 
	{1, 1, 1, 1}}, 
	{{1, 1, 1, 1}, 
	{1, 1, 1, 1}}};

/* Function Prototypes */

int fPULSE_LightController (unsigned char name_);
void fINIT_LightController (void);

/* Input Channel Functions */

int fPULSE_LightController (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE IS_OFF  ***/
	case O1_IS_OFF:		/***  PULSE CAST from PROCESS LightDimmer  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE automatic */
			switch (status_LightController.read_access_.STATE)
			{
			case 3:  /* STATE TurningOff */
				status_LightController.write_access_.STATE = 1;  /* STATE Off */
				fPULSE_AmbientLight (O8_IS_OFF);
				fPULSE_Light (O8_IS_OFF);
				fPULSE_LightSwitch (O8_IS_OFF);
				break;
			default: 
				break;
			}
			break;
		case 1:  /* MODE manual */
			switch (status_LightController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_LightController.write_access_.STATE = 1;  /* STATE Off */
				fPULSE_AmbientLight (O8_IS_OFF);
				fPULSE_Light (O8_IS_OFF);
				fPULSE_LightSwitch (O8_IS_OFF);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE IS_ON  ***/
	case O1_IS_ON:		/***  PULSE CAST from PROCESS LightDimmer  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE automatic */
			switch (status_LightController.read_access_.STATE)
			{
			case 4:  /* STATE TurningOn */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_LightSwitch (O8_IS_ON);
				break;
			default: 
				break;
			}
			break;
		case 1:  /* MODE manual */
			switch (status_LightController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_LightSwitch (O8_IS_ON);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE TURN_OFF  ***/
	case O2_OFF:		/***  PULSE CAST from PROCESS LightSwitch  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE automatic */
			switch (status_LightController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_LightController.write_access_.STATE = 3;  /* STATE TurningOff */
				fPULSE_AmbientLight (O8_TURN_OFF);
				fPULSE_Light (O8_TURN_OFF);
				fPULSE_LightDimmer (O8_TURN_OFF);
				break;
			case 4:  /* STATE TurningOn */
				status_LightController.write_access_.STATE = 3;  /* STATE TurningOff */
				fPULSE_AmbientLight (O8_TURN_OFF);
				fPULSE_Light (O8_TURN_OFF);
				fPULSE_LightDimmer (O8_TURN_OFF);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE TURN_OFF_STEP  ***/
	case O9_PRESS:		/***  PULSE CAST from PROCESS LightMinusButton  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE manual */
			switch (status_LightController.read_access_.STATE)
			{
			case 2:  /* STATE On */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_AmbientLight (O8_TURN_OFF_STEP);
				fPULSE_Light (O8_TURN_OFF_STEP);
				fPULSE_LightDimmer (O8_TURN_OFF_STEP);
				break;
			case 3:  /* STATE TurningOff */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_AmbientLight (O8_TURN_OFF_STEP);
				fPULSE_Light (O8_TURN_OFF_STEP);
				fPULSE_LightDimmer (O8_TURN_OFF_STEP);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE TURN_ON  ***/
	case O2_ON:		/***  PULSE CAST from PROCESS LightSwitch  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 2:  /* MODE automatic */
			switch (status_LightController.read_access_.STATE)
			{
			case 1:  /* STATE Off */
				status_LightController.write_access_.STATE = 4;  /* STATE TurningOn */
				fPULSE_AmbientLight (O8_TURN_ON);
				fPULSE_Light (O8_TURN_ON);
				fPULSE_LightDimmer (O8_TURN_ON);
				break;
			case 3:  /* STATE TurningOff */
				status_LightController.write_access_.STATE = 4;  /* STATE TurningOn */
				fPULSE_AmbientLight (O8_TURN_ON);
				fPULSE_Light (O8_TURN_ON);
				fPULSE_LightDimmer (O8_TURN_ON);
				break;
			default: 
				break;
			}
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE TURN_ON_STEP  ***/
	case O6_PRESS:		/***  PULSE CAST from PROCESS LightPlusButton  ***/
		switch (MODTAB_LightController[status_LightMinusButton.read_access_.STATE -1][status_LightPlusButton.read_access_.STATE -1][status_LightSwitch.read_access_.STATE -1])
		{
		case 1:  /* MODE manual */
			switch (status_LightController.read_access_.STATE)
			{
			case 1:  /* STATE Off */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_AmbientLight (O8_TURN_ON_STEP);
				fPULSE_Light (O8_TURN_ON_STEP);
				fPULSE_LightDimmer (O8_TURN_ON_STEP);
				break;
			case 2:  /* STATE On */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_AmbientLight (O8_TURN_ON_STEP);
				fPULSE_Light (O8_TURN_ON_STEP);
				fPULSE_LightDimmer (O8_TURN_ON_STEP);
				break;
			case 4:  /* STATE TurningOn */
				status_LightController.write_access_.STATE = 2;  /* STATE On */
				fPULSE_AmbientLight (O8_TURN_ON_STEP);
				fPULSE_Light (O8_TURN_ON_STEP);
				fPULSE_LightDimmer (O8_TURN_ON_STEP);
				break;
			default: 
				break;
			}
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

void fINIT_LightController (void)
{
	status_LightController.write_access_.STATE = 1;  /* STATE Off */
}

/*********************************************************************
	End of Module for PROCESS LightController
*********************************************************************/