
/*********************************************************************
	SYSTEM CabinetLightController
	IMPLEMENTATION Arduino
	Header File for CIP SHELL sCabinetLightController
	Filename: sCabinetLightController.h
	generated by CIP Tool(R) Version 4.41.00
		July 1, 2013  12:00:06 am
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

#define C_LeftDoorStateChange 1
#define C_LightStateChange 2
#define C_RightDoorStateChange 3

/* MESSAGE Enumeration of CHANNEL LeftDoorStateChange */

#define C1_ 0
#define C1_CLOSED 2
#define C1_OPEN 1

/* MESSAGE Enumeration of CHANNEL LightStateChange */

#define C2_ 0
#define C2_FADE_IN 1
#define C2_FADE_OUT 2

/* MESSAGE Enumeration of CHANNEL RightDoorStateChange */

#define C3_ 0
#define C3_CLOSED 2
#define C3_OPEN 1

/* Input Interface Type */

struct tIN_
{
	void (*LeftDoorStateChange) (unsigned char);
	void (*RightDoorStateChange) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*LightStateChange) (unsigned char);
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

extern struct tIN_ IN_;		/* Input Channel Interface defined in sCabinetLightController.c */
extern struct tOUT_ OUT_;		/* Output Channel Interface defined in sCabinetLightController.c */
extern struct tTRG_ TRG_;		/* Trigger Interface defined in sCabinetLightController.c */

/* Unit Initialization Function, defined in mCabinetLightController.c
	called by User to initialize CIP Machine
		returning 1 if successful
		returning 0 if failed */

int fINIT_(void);

/* User defined Initialization Function for CIP Shell Interface Initialization 
	called by Unit Initialization Function */

void iCHAN_(void);


#endif 

/*********************************************************************
	End of CIP UNIT Header File for CIP SHELL sCabinetLightController
*********************************************************************/
