
/*********************************************************************
	SYSTEM Lillebro
	IMPLEMENTATION ArduinoImpl
	CIP Connector Template Module for CIP SHELL sDriveUnit
	Filename: _conDriveUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		January 4, 2015  3:20:25 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		'unsigned char' for delays
		C-code
*********************************************************************/

/* Include Files */

#include "sDriveUnit.h"


/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_LeftMotorActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_BWD:
		/* user defined code */
		break;
	case C2_FWD:
		/* user defined code */
		break;
	case C2_STOP:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_RightMotorActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_BWD:
		/* user defined code */
		break;
	case C3_FWD:
		/* user defined code */
		break;
	case C3_STOP:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_WanderLightActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_CHANGE:
		/* user defined code */
		break;
	default: 
		break;
	}
}


/*********************************************************************
	User defined Output Channel Interface Initialization Function
*********************************************************************/

void iCHAN_(void)
{
		/* Initializing Input Error Function only if Input Error Option set */

	#ifdef _EINPUT__
		IN_.EINPUT_ = uEINPUT_;
	#endif 

		/* Initializing Output Interface */

	OUT_.LeftMotorActions = uCHAN_LeftMotorActions;
	OUT_.RightMotorActions = uCHAN_RightMotorActions;
	OUT_.WanderLightActions = uCHAN_WanderLightActions;
}


/*********************************************************************
	Execution of CIP Connector Activities
*********************************************************************/

	/* Initializing CIP Machine */

if (fINIT_())
{
	/* activation of drive loop */
}
else 
{
	/* initialization failed, abort drive */
}


/* Input Function Calls */

	/* Referenced Input Variables (examples) */

unsigned char name_Events;
unsigned char name_ProximityEvents;

	/* Calling Input Functions */

IN_.Events(name_Events);
IN_.ProximityEvents(name_ProximityEvents);


/* Trigger Function Calls */

TRG_.TICK_();		/* increment CIP Machine time by one Tick */

if (TRG_.PENDING_.ANY_)
	TRG_.STEP_();		/* perform one step, if any transition (in priority order chain, timeup, local message, auto) is pending */

if (TRG_.PENDING_.CHAIN_)
	TRG_.CHAIN_();		/* perform one chain, if any chain is pending */

if (TRG_.PENDING_.TIMEUP_)
	TRG_.TIMEUP_();		/* perform one timeup, if any timeup is pending  */

if (TRG_.PENDING_.READ_)
	TRG_.READ_();		/* perform one local read, if any local message is buffered */

if (TRG_.PENDING_.AUTO_)
	TRG_.AUTO_();		/* perform one auto, if any auto is pending */

/*********************************************************************
	End of CIP Connector Template Module for CIP SHELL sDriveUnit
*********************************************************************/