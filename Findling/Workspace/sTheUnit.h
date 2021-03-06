
/*********************************************************************
	SYSTEM Workspace
	IMPLEMENTATION Arduino
	Header File for CIP SHELL sTheUnit
	Filename: sTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		February 18, 2015  2:26:11 am
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

#define C_AmbientDimAction 4
#define C_AmbientDimReply 5
#define C_LightControllerActions 14
#define C_LightControllerEvents 13
#define C_LightDimMinusEvents 7
#define C_LightDimPlusEvents 6
#define C_LightSwitchEvent 2
#define C_SoundActions 11
#define C_SoundControlEvents 12
#define C_SoundMinusChannel 9
#define C_SoundPlusChannel 8
#define C_SoundSwitchChannel 10

/* MESSAGE Enumeration of CHANNEL LightSwitchEvent */

#define C2_ 0
#define C2_TOGGLE 1

/* MESSAGE Enumeration of CHANNEL AmbientDimAction */

#define C4_ 0
#define C4_MINUS 2
#define C4_PLUS 1

/* MESSAGE Enumeration of CHANNEL AmbientDimReply */

#define C5_ 0
#define C5_IS_OFF 1
#define C5_IS_ON 2

/* MESSAGE Enumeration of CHANNEL LightDimPlusEvents */

#define C6_ 0
#define C6_PRESS 2
#define C6_RELEASE 1

/* MESSAGE Enumeration of CHANNEL LightDimMinusEvents */

#define C7_ 0
#define C7_PRESS 1
#define C7_RELEASE 2

/* MESSAGE Enumeration of CHANNEL SoundPlusChannel */

#define C8_ 0
#define C8_PRESSED 1
#define C8_RELEASED 2

/* MESSAGE Enumeration of CHANNEL SoundMinusChannel */

#define C9_ 0
#define C9_PRESSED 1
#define C9_RELEASED 2

/* MESSAGE Enumeration of CHANNEL SoundSwitchChannel */

#define C10_ 0
#define C10_TOGGLE 3

/* MESSAGE Enumeration of CHANNEL SoundActions */

#define C11_ 0
#define C11_MINUS 2
#define C11_PLUS 1
#define C11_PLUS_STEP 3

/* MESSAGE Enumeration of CHANNEL SoundControlEvents */

#define C12_ 0
#define C12_IS_OFF 1
#define C12_IS_ON 2

/* MESSAGE Enumeration of CHANNEL LightControllerEvents */

#define C13_ 0
#define C13_IS_OFF 1
#define C13_IS_ON 2

/* MESSAGE Enumeration of CHANNEL LightControllerActions */

#define C14_ 0
#define C14_MINUS 2
#define C14_MINUS_STEP 5
#define C14_PLUS 1
#define C14_PLUS_STEP 3
#define C14_PLUS_STEP_DIRECT 4

/* Input Interface Type */

struct tIN_
{
	void (*AmbientDimReply) (unsigned char);
	void (*LightControllerEvents) (unsigned char);
	void (*LightDimMinusEvents) (unsigned char);
	void (*LightDimPlusEvents) (unsigned char);
	void (*LightSwitchEvent) (unsigned char);
	void (*SoundControlEvents) (unsigned char);
	void (*SoundMinusChannel) (unsigned char);
	void (*SoundPlusChannel) (unsigned char);
	void (*SoundSwitchChannel) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*AmbientDimAction) (unsigned char);
	void (*LightControllerActions) (unsigned char);
	void (*SoundActions) (unsigned char);
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
