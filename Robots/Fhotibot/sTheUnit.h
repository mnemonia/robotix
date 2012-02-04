
/*********************************************************************
	SYSTEM Fhotibot
	IMPLEMENTATION Arduino
	Header File for CIP SHELL sTheUnit
	Filename: sTheUnit.h
	generated by CIP Tool(R) Version 4.41.00
		February 4, 2012  1:11:16 am
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

#define C_LeftDriver 4
#define C_Radar 3
#define C_RightDriver 5

/* MESSAGE Enumeration of CHANNEL Radar */

#define C3_ 0
#define C3_Attention 2
#define C3_Clear 1
#define C3_Danger 3

/* MESSAGE Enumeration of CHANNEL LeftDriver */

#define C4_ 0
#define C4_Backward 2
#define C4_Forward 1
#define C4_Stop 3

/* MESSAGE Enumeration of CHANNEL RightDriver */

#define C5_ 0
#define C5_Backward 1
#define C5_Forward 2
#define C5_Stop 3

/* Input Interface Type */

struct tIN_
{
	void (*Radar) (unsigned char);
};

/* Output Interface Type */

struct tOUT_
{
	void (*LeftDriver) (unsigned char);
	void (*RightDriver) (unsigned char);
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
