
/*********************************************************************
	SYSTEM FrontDoor
	IMPLEMENTATION ArduinoImplementation
	Header File for CIP MACHINE mArduinoUnit
	Filename: mArduinoUnit.h
	generated by CIP Tool(R) Version 4.41.00
		November 10, 2013  8:45:12 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sArduinoUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Outpulse Types */

struct tOUTPLS_LightSwitch
{
	unsigned char  name_;
};

union tOUTPLS_Sonnerie
{
	struct tOUTPLS_LightSwitch OUTPLS_LightSwitch;
};

/* Global Output Type */

struct tCHAN_LightOutChannel
{
	unsigned char name_;
};

union tCHNOUT_mArduinoUnit
{
	struct tCHAN_LightOutChannel CHAN_LightOutChannel;
};

/* Global Table Elements */

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

/* Types for Process LightSwitch */

struct tPRSTAT_LightSwitch
{
	unsigned char STATE;
};

union tSTATUS_LightSwitch
{
	struct tPRSTAT_LightSwitch write_access_;
	const struct tPRSTAT_LightSwitch read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mArduinoUnit
*********************************************************************/
