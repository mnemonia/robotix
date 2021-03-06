
/*********************************************************************
	SYSTEM Droid
	IMPLEMENTATION Arduino
	Header File for CIP MACHINE mTheUnit
	Filename: mTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		January 6, 2012  10:28:36 am
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sTheUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Global Output Type */

struct tCHAN_Lampe
{
	unsigned char name_;
};

union tCHNOUT_mTheUnit
{
	struct tCHAN_Lampe CHAN_Lampe;
};

/* Global Table Elements */

/* Types for Process PrimitiveBehavior */

struct tPRSTAT_PrimitiveBehavior
{
	unsigned char STATE;
};

union tSTATUS_PrimitiveBehavior
{
	struct tPRSTAT_PrimitiveBehavior write_access_;
	const struct tPRSTAT_PrimitiveBehavior read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mTheUnit
*********************************************************************/
