
/*********************************************************************
	SYSTEM Droid
	visual ANIMATION Droid
	Error Header File for CIP MACHINE mDroid
	Filename: eDroid.h
	generated by CIP Tool(R) Version 4.41.00
		January 6, 2012  10:47:34 am
	activated code options:
		PENDING_ information
		call context error function
		call buffer warning function
		call buffer error function
		enable MODE inspection
		name dictionary files
		C-code
*********************************************************************/

#ifndef _EHEADER
#define _EHEADER

/* Include Files */

#include "mDroid.h"

/* Text Switch Constants */

#ifndef _ECONTXT__
	#define _ECONTXT__
#endif 

#ifndef _FULLBUF__
	#define _FULLBUF__
#endif 

#ifndef _EBUFFER__
	#define _EBUFFER__
#endif 

#ifdef _ESELPLS__
	#undef _ESELPLS__
#endif 

#ifdef _ESELMSG__
	#undef _ESELMSG__
#endif 

/* Process name_values of CIP Machine */

#ifndef _ePROC__
	#define _ePROC__

enum ePROC_
	{P_PrimitiveBehavior = 1};

#endif 

/* name_values of Modes, States and Outpulses of CIP Machine */

enum eMODES_
	{MD1_Toggle = 1};

enum eSTATES_
	{ST1_Off = 1, ST1_On = 2};

/* Error Function Parameter Types */

/* Parameter Type of Context Error Function,
	user defined function called by CIP Machine when a context error has occurred */

struct tCONTXT_
{
	int channel_;	/* enumeration value of the concerned channel */
	int message_;	/* enumeration value of the invalid message */
	enum ePROC_ process_;	/* enumeration value of the concerned process */
	enum eMODES_ mode_;	/* enumeration value of the current mode of the process */
	enum eSTATES_ state_;	/* enumeration value of the current state of the process */
};


/* Parameter Type of Internal Message Buffer Error Function,
	user defined function called by CIP Machine when a internal message buffer overflow has occurred */

struct tBUFFER_
{
	int channel_;	/* enumeration value of the concerned channel */
	int message_;	/* enumeration value of the rejected message */
};

/* Type of Error Interface */

struct tERR_
{
	void (*ECONTXT_) (struct tCONTXT_ *);	/* Pointer to User defined Context Error Function */
	void (*FULLBUF_) (void);		/* Pointer to User defined Internal Message Buffer Warning Function */
	void (*EBUFFER_) (struct tBUFFER_ *);	/* Pointer to User defined Internal Message Buffer Error Function */
};

/* External Interface Declarations */

/* Error Interface, defined in eDroid.c */

extern struct tERR_ ERR_;

/* User defined Initialization Function for Error Interface initialization 
	called by Unit Initialization Function */

void iERROR_(void);

#endif 

/*********************************************************************
	End of Error Header File for CIP MACHINE mDroid
*********************************************************************/