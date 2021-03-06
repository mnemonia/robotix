
/*********************************************************************
	SYSTEM IlluminatedTigerCabinet
	IMPLEMENTATION IlluminatedTigerCabImp
	Module for CIP MACHINE mTheUnit
	Filename: mTheUnit.c
	generated by CIP Tool(R) Version 4.41.00
		December 26, 2012  12:42:40 am
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mTheUnit.h"

/* External Declarations */

void fICHAN_CommandChannel (unsigned char name_);
void fINIT_CommandReceiver (void);
void fINIT_UpperCenterLight (void);

/* Global Declarations */

unsigned long time_mTheUnit = 0;
union tCHNOUT_mTheUnit CHNOUT_mTheUnit;

/* Function Prototypes */

void fSTEP_mTheUnit(void);
void fCHAIN_mTheUnit(void);
void fTIMEUP_mTheUnit(void);
void fREAD_mTheUnit(void);

/* AUTO_ Handler Function */

static void fAUTOHDL_mTheUnit(void)
{
		/* dummy function handling no AUTO_ */
}

/* Timer Functions */

static void fTICK_mTheUnit(void)
{
	time_mTheUnit ++;
}

/* Control Functions */

	/* Step Function for CIP Machine */

void fSTEP_mTheUnit(void)
{
	return;
}

	/* Chain Function for CIP Machine */

void fCHAIN_mTheUnit(void)
{
	return;
}

	/* Timeup Function for CIP Machine */

void fTIMEUP_mTheUnit(void)
{
	return;
}

	/* Read Function for CIP Machine */

void fREAD_mTheUnit(void)
{
	return;
}

/* Initialization Function */

int fINIT_(void)
{
	TRG_.TICK_ = fTICK_mTheUnit;
	TRG_.CHAIN_ = fCHAIN_mTheUnit;
	TRG_.TIMEUP_ = fTIMEUP_mTheUnit;
	TRG_.STEP_ = fSTEP_mTheUnit;
	TRG_.READ_ = fREAD_mTheUnit;
	TRG_.AUTO_ = fAUTOHDL_mTheUnit;
	IN_.CommandChannel = fICHAN_CommandChannel;
	iCHAN_();
	if (!OUT_.UpperCenterLightChan)
		return 0;
	fINIT_CommandReceiver ();
	fINIT_UpperCenterLight ();
	return 1;
}

/*********************************************************************
	End of Module for CIP MACHINE mTheUnit
*********************************************************************/
