
/*********************************************************************
	SYSTEM Findling01
	IMPLEMENTATION Arduino
	Header File for CIP SHELL sTheUnit
	Filename: sTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		October 28, 2014  9:46:14 pm
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

#define C_LightActionOut 9
#define C_LightBrightnessIn 7
#define C_LightSwitchIn 5
#define C_SoundActionOut 10
#define C_SoundLoudnessIn 8
#define C_SoundSwitchIn 6

/* MESSAGE Enumeration of CHANNEL LightSwitchIn */

#define C5_ 0
#define C5_TOGGLE 3

/* MESSAGE Enumeration of CHANNEL SoundSwitchIn */

#define C6_ 0
#define C6_TOGGLE 3

/* MESSAGE Enumeration of CHANNEL LightBrightnessIn */

#define C7_ 0
#define C7_MINUS 3
#define C7_PLUS 2

/* MESSAGE Enumeration of CHANNEL SoundLoudnessIn */

#define C8_ 0
#define C8_MINUS 2
#define C8_PLUS 1

/* MESSAGE Enumeration of CHANNEL LightActionOut */

#define C9_ 0
#define C9_MINUS 4
#define C9_OFF 2
#define C9_ON 1
#define C9_PLUS 3

/* MESSAGE Enumeration of CHANNEL SoundActionOut */

#define C10_ 0
#define C10_MINUS 4
#define C10_OFF 2
#define C10_ON 1
#define C10_PLUS 3

/* Input Interface Type */

struct tIN_
{
	void (*LightBrightnessIn) (unsigned char);
	void (*LightSwitchIn) (unsigned char);
	void (*SoundLoudnessIn) (unsigned char);
	void (*SoundSwitchIn) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*LightActionOut) (unsigned char);
	void (*SoundActionOut) (unsigned char);
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
