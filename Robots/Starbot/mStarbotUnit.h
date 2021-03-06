
/*********************************************************************
	SYSTEM Starbot
	IMPLEMENTATION StarbotImpl
	Header File for CIP MACHINE mStarbotUnit
	Filename: mStarbotUnit.h
	generated by CIP Tool(R) Version 4.41.00
		June 12, 2012  12:31:41 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _MHEADER
#define _MHEADER

/* Include Files */

#include <stdlib.h>
#include "sStarbotUnit.h"

/* Macro Definitions */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


/* Outpulse Types */

struct tOUTPLS_Attrack
{
	unsigned char  name_;
};

struct tOUTPLS_Start
{
	unsigned char  name_;
};

union tOUTPLS_Behavior
{
	struct tOUTPLS_Attrack OUTPLS_Attrack;
	struct tOUTPLS_Start OUTPLS_Start;
};

/* Global Output Type */

struct tCHAN_DetectChannel
{
	unsigned char name_;
};

struct tCHAN_ShineChannel
{
	unsigned char name_;
};

struct tCHAN_AttrackChannel
{
	unsigned char name_;
};

struct tCHAN_TrackOutChannel
{
	unsigned char name_;
};

union tCHNOUT_mStarbotUnit
{
	struct tCHAN_AttrackChannel CHAN_AttrackChannel;
	struct tCHAN_DetectChannel CHAN_DetectChannel;
	struct tCHAN_ShineChannel CHAN_ShineChannel;
	struct tCHAN_TrackOutChannel CHAN_TrackOutChannel;
};

/* Timer- and Queue-Element */

struct tTMEL_mStarbotUnit
{
	unsigned char set_; /* Boolean */
	unsigned long end_;
};

struct tTMQE_mStarbotUnit
{
	struct tTMQE_mStarbotUnit *preced_;
	struct tTMQE_mStarbotUnit *next_;
	int proctype_;
};

/* Global Table Elements */

struct tTIMING_mStarbotUnit
{
	void  (*tkhndl_) (void);
	void  (*tuhndl_) (void);
	int  set_;
};

/* Types for Process Attrack */

struct tPRSTAT_Attrack
{
	unsigned char STATE;
};

union tSTATUS_Attrack
{
	struct tPRSTAT_Attrack write_access_;
	const struct tPRSTAT_Attrack read_access_;
};

struct tPRINST_Attrack
{
	struct tTMEL_mStarbotUnit timer_;
	struct tTMQE_mStarbotUnit timeup_;
};

/* Types for Process Shine */

struct tPRSTAT_Shine
{
	unsigned char STATE;
};

union tSTATUS_Shine
{
	struct tPRSTAT_Shine write_access_;
	const struct tPRSTAT_Shine read_access_;
};

struct tPRINST_Shine
{
	struct tTMEL_mStarbotUnit timer_;
	struct tTMQE_mStarbotUnit timeup_;
};

/* Types for Process Start */

struct tPRSTAT_Start
{
	unsigned char STATE;
};

union tSTATUS_Start
{
	struct tPRSTAT_Start write_access_;
	const struct tPRSTAT_Start read_access_;
};

/* Types for Process Track */

struct tPRSTAT_Track
{
	unsigned char STATE;
};

union tSTATUS_Track
{
	struct tPRSTAT_Track write_access_;
	const struct tPRSTAT_Track read_access_;
};

struct tPRINST_Track
{
	struct tTMEL_mStarbotUnit timer_;
	struct tTMQE_mStarbotUnit timeup_;
};

#endif 

/*********************************************************************
	End of Header File for CIP MACHINE mStarbotUnit
*********************************************************************/
