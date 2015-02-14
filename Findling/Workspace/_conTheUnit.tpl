
/*********************************************************************
	SYSTEM Workspace
	IMPLEMENTATION Arduino
	CIP Connector Template Module for CIP SHELL sTheUnit
	Filename: _conTheUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		February 14, 2015  2:52:46 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "sTheUnit.h"


/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_AmbientDimAction (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_MINUS:
		/* user defined code */
		break;
	case C4_PLUS:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_LightSwitchAction (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C1_MINUS:
		/* user defined code */
		break;
	case C1_PLUS:
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

	OUT_.AmbientDimAction = uCHAN_AmbientDimAction;
	OUT_.LightSwitchAction = uCHAN_LightSwitchAction;
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

unsigned char name_AmbientDimReply;
unsigned char name_LightSwitchDimReply;
unsigned char name_LightSwitchEvent;

	/* Calling Input Functions */

IN_.AmbientDimReply(name_AmbientDimReply);
IN_.LightSwitchDimReply(name_LightSwitchDimReply);
IN_.LightSwitchEvent(name_LightSwitchEvent);


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
	End of CIP Connector Template Module for CIP SHELL sTheUnit
*********************************************************************/
