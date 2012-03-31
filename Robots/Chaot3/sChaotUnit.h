
/*********************************************************************
	SYSTEM Chaot
	IMPLEMENTATION ChaotImpl
	Header File for CIP SHELL sChaotUnit
	Filename: sChaotUnit.h
	generated by CIP Tool(R) Version 4.41.00
		March 31, 2012  2:06:00 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

#ifndef _SHEADER
#define _SHEADER

/* Code Option Constants */

#ifdef _EINPUT__
	#undef _EINPUT__
#endif 

/* Channel Enumerations */

#define C_ControllerActions 6
#define C_IndicatorActions 5
#define C_MeasureActions 3
#define C_MeasureEvents 4
#define C_ShakerActions 2
#define C_Start 1

/* MESSAGE Enumeration of CHANNEL Start */

#define C1_ 0
#define C1_START 1

/* MESSAGE Enumeration of CHANNEL ShakerActions */

#define C2_ 0
#define C2_CENTER 1
#define C2_LEFT 2
#define C2_RIGHT 3

/* MESSAGE Enumeration of CHANNEL MeasureActions */

#define C3_ 0
#define C3_MEASURE 1

/* MESSAGE Enumeration of CHANNEL MeasureEvents */

#define C4_ 0
#define C4_DONE 1

/* MESSAGE Enumeration of CHANNEL IndicatorActions */

#define C5_ 0
#define C5_INDICATE_HIGH 1
#define C5_INDICATE_LOW 3
#define C5_INDICATE_MEDIUM 4
#define C5_RESET 2

/* MESSAGE Enumeration of CHANNEL ControllerActions */

#define C6_ 0
#define C6_DRAWED 1

/* Input Interface Type */

struct tIN_
{
	void (*MeasureEvents) (unsigned char);
	void (*Start) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*ControllerActions) (unsigned char);
	void (*IndicatorActions) (unsigned char);
	void (*MeasureActions) (unsigned char);
	void (*ShakerActions) (unsigned char);
};

/* Trigger Interface Type */

struct tPENDING_
{
	int ANY_;	/* boolean indicating any pending transitions */
	int CHAIN_;	/* boolean indicating pending CHAIN_ */
	int TIMEUP_;	/* boolean indicating pending TIMEUP_ */
	int READ_;	/* boolean indicating buffered internal message */
	int AUTO_;	/* boolean indicating reading AUTO_ */
};

struct tTRG_
{
	void (*TICK_) (void);		/* increment CIP MACHINE time */
	void (*STEP_) (void);		/* trigger CIP MACHINE transition */
	void (*CHAIN_) (void);		/* trigger pending chain CIP MACHINE transition */
	void (*TIMEUP_) (void);		/* trigger pending timeup CIP MACHINE transition */
	void (*READ_) (void);		/* trigger CIP MACHINE to read from internal message buffer */
	void (*AUTO_) (void);		/* trigger pending auto CIP MACHINE transition */
	struct tPENDING_ PENDING_;		/* information on pending transitions */
};

/* External Interface Declarations */

extern struct tIN_ IN_;		/* Input Channel Interface defined in sChaotUnit.c */
extern struct tOUT_ OUT_;		/* Output Channel Interface defined in sChaotUnit.c */
extern struct tTRG_ TRG_;		/* Trigger Interface defined in sChaotUnit.c */

/* Unit Initialization Function, defined in mChaotUnit.c
	called by User to initialize CIP Machine
		returning 1 if successful
		returning 0 if failed */

int fINIT_(void);

/* User defined Initialization Function for CIP Shell Interface Initialization 
	called by Unit Initialization Function */

void iCHAN_(void);


#endif 

/*********************************************************************
	End of CIP UNIT Header File for CIP SHELL sChaotUnit
*********************************************************************/
