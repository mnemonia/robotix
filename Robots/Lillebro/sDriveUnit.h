
/*********************************************************************
	SYSTEM Lillebro
	IMPLEMENTATION ArduinoImpl
	Header File for CIP SHELL sDriveUnit
	Filename: sDriveUnit.h
	generated by CIP Tool(R) Version 4.41.00
		January 4, 2015  4:10:33 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned char' for delays
		C-code
*********************************************************************/

#ifndef _SHEADER
#define _SHEADER

/* Code Option Constants */

#ifdef _EINPUT__
	#undef _EINPUT__
#endif 

/* Channel Enumerations */

#define C_Events 1
#define C_LeftMotorActions 2
#define C_ProximityEvents 4
#define C_RightMotorActions 3
#define C_WanderLightActions 5

/* MESSAGE Enumeration of CHANNEL Events */

#define C1_ 0
#define C1_TRIGGER 1

/* MESSAGE Enumeration of CHANNEL LeftMotorActions */

#define C2_ 0
#define C2_BWD 1
#define C2_FWD 3
#define C2_STOP 2

/* MESSAGE Enumeration of CHANNEL RightMotorActions */

#define C3_ 0
#define C3_BWD 1
#define C3_FWD 3
#define C3_STOP 2

/* MESSAGE Enumeration of CHANNEL ProximityEvents */

#define C4_ 0
#define C4_ATTENTION 1
#define C4_CLEAR 3
#define C4_DANGER 2

/* MESSAGE Enumeration of CHANNEL WanderLightActions */

#define C5_ 0
#define C5_CHANGE 1

/* Input Interface Type */

struct tIN_
{
	void (*Events) (unsigned char);
	void (*ProximityEvents) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*LeftMotorActions) (unsigned char);
	void (*RightMotorActions) (unsigned char);
	void (*WanderLightActions) (unsigned char);
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

extern struct tIN_ IN_;		/* Input Channel Interface defined in sDriveUnit.c */
extern struct tOUT_ OUT_;		/* Output Channel Interface defined in sDriveUnit.c */
extern struct tTRG_ TRG_;		/* Trigger Interface defined in sDriveUnit.c */

/* Unit Initialization Function, defined in mDriveUnit.c
	called by User to initialize CIP Machine
		returning 1 if successful
		returning 0 if failed */

int fINIT_(void);

/* User defined Initialization Function for CIP Shell Interface Initialization 
	called by Unit Initialization Function */

void iCHAN_(void);


#endif 

/*********************************************************************
	End of CIP UNIT Header File for CIP SHELL sDriveUnit
*********************************************************************/
