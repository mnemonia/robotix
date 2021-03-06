
/*********************************************************************
	SYSTEM Instrument
	IMPLEMENTATION InstrumentImpl
	Header File for CIP MACHINE mInstrumentUnit
	Filename: mInstrumentUnit.h
	generated by CIP Tool(R) Version 4.41.00
		July 12, 2012  9:11:11 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sInstrumentUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Global Output Type */

struct tCHAN_E_OutChannel
{
	unsigned char name_;
};

union tCHNOUT_mInstrumentUnit
{
	struct tCHAN_E_OutChannel CHAN_E_OutChannel;
};

/* Global Table Elements */

/* Types for Process Finger */

struct tPRSTAT_Finger
{
	unsigned char STATE;
};

union tSTATUS_Finger
{
	struct tPRSTAT_Finger write_access_;
	const struct tPRSTAT_Finger read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mInstrumentUnit
*********************************************************************/
