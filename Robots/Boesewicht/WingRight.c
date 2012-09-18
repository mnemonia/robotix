
/*********************************************************************
	SYSTEM Boesewicht
	Module for PROCESS WingRight
	Filename: WingRight.c
	generated by CIP Tool(R) Version 4.41.00
		September 19, 2012  12:35:52 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mBoesewicht.h"

/* Process Macro Definitions */

#define SELF status_WingRight.write_access_
#define STATUS status_WingRight.read_access_
#define TIME time_mBoesewicht

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Bottom 1
#define Center 2
#define Top 3


/* INPULSES */
#define IP_NEUTRAL 1
#define IP_DOWN 2
#define IP_UP 3


/* OUTPULSES */

#define O7_PLAY 8
#define O7_WAIT 9
#define O7_WAKEUP 7
#define O4_OPEN_EYES 4
#define O4_PLAY 5
#define O4_WAVE 3
#define O3_DOWN 2
#define O3_NEUTRAL 6
#define O3_UP 1
#define O8_Still 10

/* External Declarations */

extern unsigned long time_mBoesewicht;
extern union tCHNOUT_mBoesewicht CHNOUT_mBoesewicht;

void fUPDATE_Robot (void);

/* Global Declarations */

union tSTATUS_WingRight status_WingRight;

/* Function Prototypes */

int fPULSE_WingRight (unsigned char name_);
void fINIT_WingRight (void);

/* Input Channel Functions */

int fPULSE_WingRight (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE DOWN  ***/
	case O3_DOWN:		/***  PULSE CAST from PROCESS WaveWings  ***/
		switch (status_WingRight.read_access_.STATE)
		{
		case 2:  /* STATE Center */
			status_WingRight.write_access_.STATE = 1;  /* STATE Bottom */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_BOTTOM;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
			break;
		case 3:  /* STATE Top */
			status_WingRight.write_access_.STATE = 1;  /* STATE Bottom */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_BOTTOM;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE NEUTRAL  ***/
	case O3_NEUTRAL:		/***  PULSE CAST from PROCESS WaveWings  ***/
		switch (status_WingRight.read_access_.STATE)
		{
		case 1:  /* STATE Bottom */
			status_WingRight.write_access_.STATE = 2;  /* STATE Center */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_CENTER;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
			break;
		case 3:  /* STATE Top */
			status_WingRight.write_access_.STATE = 2;  /* STATE Center */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_CENTER;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
			break;
		default: 
			break;
		}
		break;
		/***  INPULSE UP  ***/
	case O3_UP:		/***  PULSE CAST from PROCESS WaveWings  ***/
		switch (status_WingRight.read_access_.STATE)
		{
		case 1:  /* STATE Bottom */
			status_WingRight.write_access_.STATE = 3;  /* STATE Top */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_TOP;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
			break;
		case 2:  /* STATE Center */
			status_WingRight.write_access_.STATE = 3;  /* STATE Top */
			CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_ = C2_TOP;
			OUT_.WingRightChannel (CHNOUT_mBoesewicht.CHAN_WingRightChannel.name_);
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

void fINIT_WingRight (void)
{
	status_WingRight.write_access_.STATE = 2;  /* STATE Center */
}

/*********************************************************************
	End of Module for PROCESS WingRight
*********************************************************************/
