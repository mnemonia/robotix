
/*********************************************************************
	SYSTEM Lillebro
	IMPLEMENTATION ArduinoImpl
	Header File for CIP MACHINE mDriveUnit
	Filename: mDriveUnit.h
	generated by CIP Tool(R) Version 4.41.00
		January 4, 2015  3:20:27 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned char' for delays
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sDriveUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Outpulse Types */

struct tOUTPLS_Behavior
{
	unsigned char  name_;
};

struct tOUTPLS_Demo
{
	unsigned char  name_;
};

struct tOUTPLS_Drive
{
	unsigned char  name_;
};

struct tOUTPLS_IndicatorLight
{
	unsigned char  name_;
};

struct tOUTPLS_Proximity
{
	unsigned char  name_;
};

union tOUTPLS_Controller
{
	struct tOUTPLS_Behavior OUTPLS_Behavior;
	struct tOUTPLS_Demo OUTPLS_Demo;
	struct tOUTPLS_Drive OUTPLS_Drive;
	struct tOUTPLS_IndicatorLight OUTPLS_IndicatorLight;
	struct tOUTPLS_Proximity OUTPLS_Proximity;
};

/* Global Output Type */

struct tCHAN_RightMotorActions
{
	unsigned char name_;
};

struct tCHAN_LeftMotorActions
{
	unsigned char name_;
};

struct tCHAN_WanderLightActions
{
	unsigned char name_;
};

union tCHNOUT_mDriveUnit
{
	struct tCHAN_LeftMotorActions CHAN_LeftMotorActions;
	struct tCHAN_RightMotorActions CHAN_RightMotorActions;
	struct tCHAN_WanderLightActions CHAN_WanderLightActions;
};

/* Timer- and Queue-Element */

struct tTMEL_mDriveUnit
{
	unsigned char set_; /* Boolean */
	unsigned char end_;
};

struct tTMQE_mDriveUnit
{
	struct tTMQE_mDriveUnit *preced_;
	struct tTMQE_mDriveUnit *next_;
	int proctype_;
};

/* Global Table Elements */

struct tTIMING_mDriveUnit
{
	void  (*tkhndl_) (void);
	void  (*tuhndl_) (void);
	int  set_;
};

/* Types for Process Behavior */

struct tPRSTAT_Behavior
{
	unsigned char STATE;
};

union tSTATUS_Behavior
{
	struct tPRSTAT_Behavior write_access_;
	const struct tPRSTAT_Behavior read_access_;
};

/* Types for Process Demo */

struct tPRSTAT_Demo
{
	unsigned char STATE;
};

union tSTATUS_Demo
{
	struct tPRSTAT_Demo write_access_;
	const struct tPRSTAT_Demo read_access_;
};

struct tPRINST_Demo
{
	struct tTMEL_mDriveUnit timer_;
	struct tTMQE_mDriveUnit timeup_;
};

/* Types for Process Drive */

struct tPRSTAT_Drive
{
	unsigned char STATE;
};

union tSTATUS_Drive
{
	struct tPRSTAT_Drive write_access_;
	const struct tPRSTAT_Drive read_access_;
};

/* Types for Process IndicatorLight */

struct tPRSTAT_IndicatorLight
{
	unsigned char STATE;
};

union tSTATUS_IndicatorLight
{
	struct tPRSTAT_IndicatorLight write_access_;
	const struct tPRSTAT_IndicatorLight read_access_;
};

/* Types for Process MotorLeft */

struct tPRSTAT_MotorLeft
{
	unsigned char STATE;
};

union tSTATUS_MotorLeft
{
	struct tPRSTAT_MotorLeft write_access_;
	const struct tPRSTAT_MotorLeft read_access_;
};

/* Types for Process MotorRight */

struct tPRSTAT_MotorRight
{
	unsigned char STATE;
};

union tSTATUS_MotorRight
{
	struct tPRSTAT_MotorRight write_access_;
	const struct tPRSTAT_MotorRight read_access_;
};

/* Types for Process Proximity */

struct tPRSTAT_Proximity
{
	unsigned char STATE;
};

union tSTATUS_Proximity
{
	struct tPRSTAT_Proximity write_access_;
	const struct tPRSTAT_Proximity read_access_;
};

/* Types for Process WanderLightController */

struct tPRSTAT_WanderLightController
{
	unsigned char STATE;
};

union tSTATUS_WanderLightController
{
	struct tPRSTAT_WanderLightController write_access_;
	const struct tPRSTAT_WanderLightController read_access_;
};

struct tPRINST_WanderLightController
{
	struct tTMEL_mDriveUnit timer_;
	struct tTMQE_mDriveUnit timeup_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mDriveUnit
*********************************************************************/