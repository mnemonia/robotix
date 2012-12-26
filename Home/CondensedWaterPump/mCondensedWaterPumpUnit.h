
/*********************************************************************
	SYSTEM CondensedWaterPump
	IMPLEMENTATION CondensedWaterPumpImpl
	Header File for CIP MACHINE mCondensedWaterPumpUnit
	Filename: mCondensedWaterPumpUnit.h
	generated by CIP Tool(R) Version 4.41.00
		December 18, 2012  8:00:09 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sCondensedWaterPumpUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Outpulse Types */

struct tOUTPLS_LowerLevelSensor
{
	unsigned char  name_;
};

struct tOUTPLS_ThreeStepController
{
	unsigned char  name_;
};

struct tOUTPLS_UpperLevelSensor
{
	unsigned char  name_;
};

union tOUTPLS_PumpController
{
	struct tOUTPLS_LowerLevelSensor OUTPLS_LowerLevelSensor;
	struct tOUTPLS_ThreeStepController OUTPLS_ThreeStepController;
	struct tOUTPLS_UpperLevelSensor OUTPLS_UpperLevelSensor;
};

/* Global Output Type */

struct tCHAN_PumpOutChannel
{
	unsigned char name_;
};

union tCHNOUT_mCondensedWaterPumpUnit
{
	struct tCHAN_PumpOutChannel CHAN_PumpOutChannel;
};

/* Global Table Elements */

/* Types for Process LowerLevelSensor */

struct tPRSTAT_LowerLevelSensor
{
	unsigned char STATE;
};

union tSTATUS_LowerLevelSensor
{
	struct tPRSTAT_LowerLevelSensor write_access_;
	const struct tPRSTAT_LowerLevelSensor read_access_;
};

/* Types for Process Pump */

struct tPRSTAT_Pump
{
	unsigned char STATE;
};

union tSTATUS_Pump
{
	struct tPRSTAT_Pump write_access_;
	const struct tPRSTAT_Pump read_access_;
};

/* Types for Process ThreeStepController */

struct tPRSTAT_ThreeStepController
{
	unsigned char STATE;
};

union tSTATUS_ThreeStepController
{
	struct tPRSTAT_ThreeStepController write_access_;
	const struct tPRSTAT_ThreeStepController read_access_;
};

/* Types for Process UpperLevelSensor */

struct tPRSTAT_UpperLevelSensor
{
	unsigned char STATE;
};

union tSTATUS_UpperLevelSensor
{
	struct tPRSTAT_UpperLevelSensor write_access_;
	const struct tPRSTAT_UpperLevelSensor read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mCondensedWaterPumpUnit
*********************************************************************/