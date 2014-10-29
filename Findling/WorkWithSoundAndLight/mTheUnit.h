
/*********************************************************************
	SYSTEM Findling01
	IMPLEMENTATION Arduino
	Header File for CIP MACHINE mTheUnit
	Filename: mTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		October 29, 2014  7:18:35 pm
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

struct tCHAN_SoundActionOut
{
	unsigned char name_;
};

struct tCHAN_AmbientAction
{
	unsigned char name_;
};

struct tCHAN_LightActionOut
{
	unsigned char name_;
};

union tCHNOUT_mTheUnit
{
	struct tCHAN_AmbientAction CHAN_AmbientAction;
	struct tCHAN_LightActionOut CHAN_LightActionOut;
	struct tCHAN_SoundActionOut CHAN_SoundActionOut;
};

/* Global Table Elements */

/* Types for Process Ambient */

struct tPRSTAT_Ambient
{
	unsigned char STATE;
};

union tSTATUS_Ambient
{
	struct tPRSTAT_Ambient write_access_;
	const struct tPRSTAT_Ambient read_access_;
};

/* Types for Process Light */

struct tPRSTAT_Light
{
	unsigned char STATE;
};

union tSTATUS_Light
{
	struct tPRSTAT_Light write_access_;
	const struct tPRSTAT_Light read_access_;
};

/* Types for Process Sound */

struct tPRSTAT_Sound
{
	unsigned char STATE;
};

union tSTATUS_Sound
{
	struct tPRSTAT_Sound write_access_;
	const struct tPRSTAT_Sound read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mTheUnit
*********************************************************************/
