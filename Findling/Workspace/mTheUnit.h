
/*********************************************************************
	SYSTEM Workspace
	IMPLEMENTATION Arduino
	Header File for CIP MACHINE mTheUnit
	Filename: mTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		February 14, 2015  2:52:48 am
	activated code options:
		PENDING_ information
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


/* Outpulse Types */

struct tOUTPLS_AmbientLight
{
	unsigned char  name_;
};

struct tOUTPLS_Light
{
	unsigned char  name_;
};

struct tOUTPLS_LightDimmer
{
	unsigned char  name_;
};

struct tOUTPLS_LightSwitch
{
	unsigned char  name_;
};

union tOUTPLS_Controller
{
	struct tOUTPLS_AmbientLight OUTPLS_AmbientLight;
	struct tOUTPLS_Light OUTPLS_Light;
	struct tOUTPLS_LightDimmer OUTPLS_LightDimmer;
	struct tOUTPLS_LightSwitch OUTPLS_LightSwitch;
};

/* Global Output Type */

struct tCHAN_LightSwitchAction
{
	unsigned char name_;
};

struct tCHAN_AmbientDimAction
{
	unsigned char name_;
};

union tCHNOUT_mTheUnit
{
	struct tCHAN_AmbientDimAction CHAN_AmbientDimAction;
	struct tCHAN_LightSwitchAction CHAN_LightSwitchAction;
};

/* Timer- and Queue-Element */

struct tTMEL_mTheUnit
{
	unsigned char set_; /* Boolean */
	unsigned long end_;
};

struct tTMQE_mTheUnit
{
	struct tTMQE_mTheUnit *preced_;
	struct tTMQE_mTheUnit *next_;
	int proctype_;
};

/* Global Table Elements */

struct tTIMING_mTheUnit
{
	void  (*tkhndl_) (void);
	void  (*tuhndl_) (void);
	int  set_;
};

/* Types for Process AmbientLight */

struct tPRSTAT_AmbientLight
{
	unsigned char STATE;
};

union tSTATUS_AmbientLight
{
	struct tPRSTAT_AmbientLight write_access_;
	const struct tPRSTAT_AmbientLight read_access_;
};

/* Types for Process AmbientLightDimmer */

struct tPRSTAT_AmbientLightDimmer
{
	unsigned char STATE;
};

union tSTATUS_AmbientLightDimmer
{
	struct tPRSTAT_AmbientLightDimmer write_access_;
	const struct tPRSTAT_AmbientLightDimmer read_access_;
};

struct tPRINST_AmbientLightDimmer
{
	struct tTMEL_mTheUnit timer_;
	struct tTMQE_mTheUnit timeup_;
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

/* Types for Process LightDimmer */

struct tPRSTAT_LightDimmer
{
	unsigned char STATE;
};

union tSTATUS_LightDimmer
{
	struct tPRSTAT_LightDimmer write_access_;
	const struct tPRSTAT_LightDimmer read_access_;
};

struct tPRINST_LightDimmer
{
	struct tTMEL_mTheUnit timer_;
	struct tTMQE_mTheUnit timeup_;
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
	End of Header File for CIP MACHINE mTheUnit
*********************************************************************/
