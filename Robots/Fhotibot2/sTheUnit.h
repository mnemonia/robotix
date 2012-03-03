
/*********************************************************************
	SYSTEM Fhotibot2
	IMPLEMENTATION Arduino
	Header File for CIP SHELL sTheUnit
	Filename: sTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		March 3, 2012  9:58:34 pm
	activated code options:
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

#define C_BumperInfo 4
#define C_MotorLeftActions 2
#define C_MotorRightActions 3
#define C_ObjectAvoidanceInfo 5
#define C_PositionInfo 1

/* MESSAGE Enumeration of CHANNEL PositionInfo */

#define C1_ 0
#define C1_Ahead 1
#define C1_Left 2
#define C1_Right 3
#define C1_Unknown 4

/* MESSAGE Enumeration of CHANNEL MotorLeftActions */

#define C2_ 0
#define C2_BWD 3
#define C2_FWD 2
#define C2_STOP 1

/* MESSAGE Enumeration of CHANNEL MotorRightActions */

#define C3_ 0
#define C3_BWD 1
#define C3_FWD 2
#define C3_STOP 3

/* MESSAGE Enumeration of CHANNEL BumperInfo */

#define C4_ 0
#define C4_HITTED 1
#define C4_RELEASED 2

/* MESSAGE Enumeration of CHANNEL ObjectAvoidanceInfo */

#define C5_ 0
#define C5_ATTENTION 1
#define C5_CLEAR 3
#define C5_DANGER 2

/* Input Interface Type */

struct tIN_
{
	void (*BumperInfo) (unsigned char);
	void (*ObjectAvoidanceInfo) (unsigned char);
	void (*PositionInfo) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*MotorLeftActions) (unsigned char);
	void (*MotorRightActions) (unsigned char);
};

/* Trigger Interface Type */

struct tTRG_
{
	void (*TICK_) (void);		/* increment CIP MACHINE time */
	void (*STEP_) (void);		/* trigger CIP MACHINE transition */
	void (*CHAIN_) (void);		/* trigger pending chain CIP MACHINE transition */
	void (*TIMEUP_) (void);		/* trigger pending timeup CIP MACHINE transition */
	void (*READ_) (void);		/* trigger CIP MACHINE to read from internal message buffer */
	void (*AUTO_) (void);		/* trigger pending auto CIP MACHINE transition */
};

/* External Interface Declarations */

extern struct tIN_ IN_;		/* Input Channel Interface defined in sTheUnit.c */
extern struct tOUT_ OUT_;		/* Output Channel Interface defined in sTheUnit.c */
extern struct tTRG_ TRG_;		/* Trigger Interface defined in sTheUnit.c */

/* Unit Initialization Function, defined in mTheUnit.c
	called by User to initialize CIP Machine
		returning 1 if successful
		returning 0 if failed */

int fINIT_(void);

/* User defined Initialization Function for CIP Shell Interface Initialization 
	called by Unit Initialization Function */

void iCHAN_(void);


#endif 

/*********************************************************************
	End of CIP UNIT Header File for CIP SHELL sTheUnit
*********************************************************************/
