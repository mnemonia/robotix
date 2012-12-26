
/*********************************************************************
	SYSTEM CondensedWaterPump
	IMPLEMENTATION CondensedWaterPumpImpl
	Header File for CIP SHELL sCondensedWaterPumpUnit
	Filename: sCondensedWaterPumpUnit.h
	generated by CIP Tool(R) Version 4.41.00
		December 18, 2012  8:00:07 pm
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

#define C_LowerLevelSensorInChan 3
#define C_PumpOutChannel 2
#define C_UpperLevelSensorInChan 4

/* MESSAGE Enumeration of CHANNEL PumpOutChannel */

#define C2_ 0
#define C2_OFF 1
#define C2_ON 2

/* MESSAGE Enumeration of CHANNEL LowerLevelSensorInChan */

#define C3_ 0
#define C3_HIGH 2
#define C3_LOW 1

/* MESSAGE Enumeration of CHANNEL UpperLevelSensorInChan */

#define C4_ 0
#define C4_HIGH 2
#define C4_LOW 1

/* Input Interface Type */

struct tIN_
{
	void (*LowerLevelSensorInChan) (unsigned char);
	void (*UpperLevelSensorInChan) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*PumpOutChannel) (unsigned char);
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

extern struct tIN_ IN_;		/* Input Channel Interface defined in sCondensedWaterPumpUnit.c */
extern struct tOUT_ OUT_;		/* Output Channel Interface defined in sCondensedWaterPumpUnit.c */
extern struct tTRG_ TRG_;		/* Trigger Interface defined in sCondensedWaterPumpUnit.c */

/* Unit Initialization Function, defined in mCondensedWaterPumpUnit.c
	called by User to initialize CIP Machine
		returning 1 if successful
		returning 0 if failed */

int fINIT_(void);

/* User defined Initialization Function for CIP Shell Interface Initialization 
	called by Unit Initialization Function */

void iCHAN_(void);


#endif 

/*********************************************************************
	End of CIP UNIT Header File for CIP SHELL sCondensedWaterPumpUnit
*********************************************************************/