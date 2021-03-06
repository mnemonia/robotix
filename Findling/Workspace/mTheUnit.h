
/*********************************************************************
	SYSTEM Workspace
	IMPLEMENTATION Arduino
	Header File for CIP MACHINE mTheUnit
	Filename: mTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		February 18, 2015  2:26:12 am
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

struct tOUTPLS_LightController
{
	unsigned char  name_;
};

struct tOUTPLS_LightMinusButton
{
	unsigned char  name_;
};

struct tOUTPLS_LightPlusButton
{
	unsigned char  name_;
};

struct tOUTPLS_LightSwitch
{
	unsigned char  name_;
};

union tOUTPLS_Lights
{
	struct tOUTPLS_AmbientLight OUTPLS_AmbientLight;
	struct tOUTPLS_LightController OUTPLS_LightController;
	struct tOUTPLS_LightMinusButton OUTPLS_LightMinusButton;
	struct tOUTPLS_LightPlusButton OUTPLS_LightPlusButton;
	struct tOUTPLS_LightSwitch OUTPLS_LightSwitch;
};

struct tOUTPLS_SoundController
{
	unsigned char  name_;
};

struct tOUTPLS_SoundMinusButton
{
	unsigned char  name_;
};

struct tOUTPLS_SoundPlusButton
{
	unsigned char  name_;
};

struct tOUTPLS_SoundSwitch
{
	unsigned char  name_;
};

union tOUTPLS_Sound
{
	struct tOUTPLS_SoundController OUTPLS_SoundController;
	struct tOUTPLS_SoundMinusButton OUTPLS_SoundMinusButton;
	struct tOUTPLS_SoundPlusButton OUTPLS_SoundPlusButton;
	struct tOUTPLS_SoundSwitch OUTPLS_SoundSwitch;
};

/* Global Output Type */

struct tCHAN_SoundActions
{
	unsigned char name_;
};

struct tCHAN_LightControllerActions
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
	struct tCHAN_LightControllerActions CHAN_LightControllerActions;
	struct tCHAN_SoundActions CHAN_SoundActions;
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

/* Types for Process LightController */

struct tPRSTAT_LightController
{
	unsigned char STATE;
};

union tSTATUS_LightController
{
	struct tPRSTAT_LightController write_access_;
	const struct tPRSTAT_LightController read_access_;
};

struct tPRINST_LightController
{
	struct tTMEL_mTheUnit timer_;
	struct tTMQE_mTheUnit timeup_;
};

/* Types for Process LightMinusButton */

struct tPRSTAT_LightMinusButton
{
	unsigned char STATE;
};

union tSTATUS_LightMinusButton
{
	struct tPRSTAT_LightMinusButton write_access_;
	const struct tPRSTAT_LightMinusButton read_access_;
};

/* Types for Process LightPlusButton */

struct tPRSTAT_LightPlusButton
{
	unsigned char STATE;
};

union tSTATUS_LightPlusButton
{
	struct tPRSTAT_LightPlusButton write_access_;
	const struct tPRSTAT_LightPlusButton read_access_;
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

struct tPRINST_LightSwitch
{
	struct tTMEL_mTheUnit timer_;
	struct tTMQE_mTheUnit timeup_;
};

/* Types for Process SoundController */

struct tPRSTAT_SoundController
{
	unsigned char STATE;
};

union tSTATUS_SoundController
{
	struct tPRSTAT_SoundController write_access_;
	const struct tPRSTAT_SoundController read_access_;
};

struct tPRINST_SoundController
{
	struct tTMEL_mTheUnit timer_;
	struct tTMQE_mTheUnit timeup_;
};

/* Types for Process SoundMinusButton */

struct tPRSTAT_SoundMinusButton
{
	unsigned char STATE;
};

union tSTATUS_SoundMinusButton
{
	struct tPRSTAT_SoundMinusButton write_access_;
	const struct tPRSTAT_SoundMinusButton read_access_;
};

/* Types for Process SoundPlusButton */

struct tPRSTAT_SoundPlusButton
{
	unsigned char STATE;
};

union tSTATUS_SoundPlusButton
{
	struct tPRSTAT_SoundPlusButton write_access_;
	const struct tPRSTAT_SoundPlusButton read_access_;
};

/* Types for Process SoundSwitch */

struct tPRSTAT_SoundSwitch
{
	unsigned char STATE;
};

union tSTATUS_SoundSwitch
{
	struct tPRSTAT_SoundSwitch write_access_;
	const struct tPRSTAT_SoundSwitch read_access_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mTheUnit
*********************************************************************/
