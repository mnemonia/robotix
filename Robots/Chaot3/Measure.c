
/*********************************************************************
	SYSTEM Chaot
	Module for PROCESS Measure
	Filename: Measure.c
	generated by CIP Tool(R) Version 4.41.00
		April 27, 2012  2:32:31 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "mChaotUnit.h"

/* Process Macro Definitions */

#define EXCEPTION return;
#define IN (*in_)
#define OUTPULSE (*outpulse_)
#define SELF status_Measure.write_access_
#define STATUS status_Measure.read_access_
#define TIME time_mChaotUnit

/* Process Definitions */

/* MODES */
#define normal 1

/* STATES */
#define Measuring 1
#define Ready 2


/* INPULSES */
#define IP_MEASURE 1


/* OUTPULSES */

#define O5_DONE 7
#define O3_SHAKE 1
#define O3_START 6
#define O2_INDICATING 5
#define O4_MEASURED 4
#define O1_DONE 3

/* External Declarations */

extern unsigned long time_mChaotUnit;
extern union tCHNOUT_mChaotUnit CHNOUT_mChaotUnit;

void fUPDATE_Robot (void);
int fPULSE_Indicator (unsigned char name_, 
	union tOUTPLS_Robot *data_);

/* Global Declarations */

union tSTATUS_Measure status_Measure;

/* Function Prototypes */

void fICHAN_MeasureEvents (unsigned char name_, 
	union tDATA_MeasureEvents *data_);
int fPULSE_Measure (unsigned char name_);
void fINIT_Measure (void);

/* Input Channel Functions */

void fICHAN_MeasureEvents (unsigned char name_, 
	union tDATA_MeasureEvents *data_)
{
	union tOUTPLS_Robot OUTPLS_Measure = {{0}};
	switch (name_)
	{
		/***  MESSAGE DONE of INPORT InMessages  ***/
	case C4_DONE:
		{
			struct tCIPREC_Results IN = &data_->_Results;
			switch (status_Measure.read_access_.STATE)
			{
			case 1:  /* STATE Measuring */
				{
					struct tCIPREC_Results OUTPULSE = &OUTPLS_Measure.OUTPLS_Measure.data_._Results;
						/***  OPERATIONS before writing  ***/
						/***  setMeasureResults  ***/
					{
					OUTPULSE.Number = IN.Number;
					}
					status_Measure.write_access_.STATE = 2;  /* STATE Ready */
					fPULSE_Indicator (O4_MEASURED, 
						&OUTPLS_Measure);
				}
				break;
			default: 
				return;
			}
		}
		break;
	default: 
		return;
	}
	fUPDATE_Robot ();
	return;
}

#undef EXCEPTION

int fPULSE_Measure (unsigned char name_)
{
	switch (name_)
	{
		/***  INPULSE MEASURE  ***/
	case O5_DONE:		/***  PULSE CAST from PROCESS Chaotic  ***/
		switch (status_Measure.read_access_.STATE)
		{
		case 2:  /* STATE Ready */
			status_Measure.write_access_.STATE = 1;  /* STATE Measuring */
			CHNOUT_mChaotUnit.CHAN_MeasureActions.name_ = C3_MEASURE;
			OUT_.MeasureActions (CHNOUT_mChaotUnit.CHAN_MeasureActions.name_);
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

void fINIT_Measure (void)
{
	status_Measure.write_access_.STATE = 2;  /* STATE Ready */
}

/*********************************************************************
	End of Module for PROCESS Measure
*********************************************************************/
