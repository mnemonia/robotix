
/*********************************************************************
	SYSTEM Droid
	Module for PROCESS PrimitiveBehavior
	Filename: PrimitiveBehavior.c
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

/* Include Files */

#include "mDroid.h"

#include "eDroid.h"

/* Process Macro Definitions */

#define EXCEPTION {contexterr_ = 1; break;}
#define SELF status_PrimitiveBehavior.write_access_
#define STATUS status_PrimitiveBehavior.read_access_
#define TIME time_mDroid

/* Process Enumerations */

enum eMODES_PrimitiveBehavior
	{Toggle = 1};

enum eSTATES_PrimitiveBehavior
	{Off = 1, On};


/* External Declarations */

extern unsigned long time_mDroid;
extern union tCHNOUT_mDroid CHNOUT_mDroid;
extern struct tCONTXT_ CONTXT_;
extern CbShowProcess_ cCbShowProcess_;
extern CbEContext_ cCbEContext_;
extern CbEFullbuff_ cCbEFullbuff_;
extern CbEBuffer_ cCbEBuffer_;
extern CbTPutString_ cCbTPutString_;

extern StatusField_ statusArray_[1];
extern TransitionField_ transitionArray_[1];

void fUPDATE_Behavior (void);
void fRESET_Behavior(void);

/* Global Declarations */

union tSTATUS_PrimitiveBehavior status_PrimitiveBehavior;

/* Function Prototypes */

void fRESET_PrimitiveBehavior (void);
void fICHAN_Schalter (int name_);
void fINIT_PrimitiveBehavior (void);

/* Update Functions */

void fRESET_PrimitiveBehavior (void)
{
	transitionArray_[0] = 0;
	statusArray_[0].sender_ = 0;
}

/* Input Channel Functions */

void fICHAN_Schalter (int name_)
{
	int contexterr_ = 0;
	fRESET_Behavior ();
	statusArray_[0].sender_ = 1;
	switch (name_)
	{
		/***  MESSAGE Off of INPORT InPort  ***/
	case C1_Off:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case On:
			status_PrimitiveBehavior.write_access_.STATE = Off;
			CHNOUT_mDroid.CHAN_Lampe.name_ = C2_Aus;
			OUT_.Lampe (CHNOUT_mDroid.CHAN_Lampe.name_);
			statusArray_[0].state_ = Off;
			transitionArray_[0] = 2;
			cCbShowProcess_(0);
			break;
		default: 
			contexterr_ = 1;
			break;
		}
		break;
		/***  MESSAGE On of INPORT InPort  ***/
	case C1_On:
		switch (status_PrimitiveBehavior.read_access_.STATE)
		{
		case Off:
			status_PrimitiveBehavior.write_access_.STATE = On;
			CHNOUT_mDroid.CHAN_Lampe.name_ = C2_Ein;
			OUT_.Lampe (CHNOUT_mDroid.CHAN_Lampe.name_);
			statusArray_[0].state_ = On;
			transitionArray_[0] = 1;
			cCbShowProcess_(0);
			break;
		default: 
			contexterr_ = 1;
			break;
		}
		break;
	default: 
		return;
	}
	if (contexterr_)
	{
		CONTXT_.process_ = P_PrimitiveBehavior;
		CONTXT_.message_ = name_;
		CONTXT_.mode_ = (enum eMODES_)Toggle;
		CONTXT_.state_ = (enum eSTATES_)status_PrimitiveBehavior.read_access_.STATE;
		CONTXT_.channel_ = C_Schalter;
		ERR_.ECONTXT_(&CONTXT_);
		fUPDATE_Behavior ();
		return;
	}
	fUPDATE_Behavior ();
	return;
}

#undef EXCEPTION

/* Process Initialization Function */

void fINIT_PrimitiveBehavior (void)
{
	transitionArray_[0] = 0;
	statusArray_[0].sender_ = 0;
	status_PrimitiveBehavior.write_access_.MODE = Toggle;
	statusArray_[0].mode_ = Toggle;
	status_PrimitiveBehavior.write_access_.STATE = Off;
	statusArray_[0].state_ = Off;
}

/*********************************************************************
	End of Module for PROCESS PrimitiveBehavior
*********************************************************************/
