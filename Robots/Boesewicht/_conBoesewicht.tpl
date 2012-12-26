
/*********************************************************************
	SYSTEM Boesewicht
	IMPLEMENTATION ArduinoImplementation
	CIP Connector Template Module for CIP SHELL sBoesewicht
	Filename: _conBoesewicht.tpl
	generated by CIP Tool(R) Version 4.41.00
		September 19, 2012  12:35:50 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "sBoesewicht.h"


/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_EyeOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_CLOSE:
		/* user defined code */
		break;
	case C3_OPEN:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_MouthOutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_CLOSE:
		/* user defined code */
		break;
	case C4_OPEN:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_WingControllerOutC (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C7_Move:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_WingLeftChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C1_BOTTOM:
		/* user defined code */
		break;
	case C1_CENTER:
		/* user defined code */
		break;
	case C1_TOP:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_WingRightChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_BOTTOM:
		/* user defined code */
		break;
	case C2_CENTER:
		/* user defined code */
		break;
	case C2_TOP:
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

	OUT_.EyeOutChannel = uCHAN_EyeOutChannel;
	OUT_.MouthOutChannel = uCHAN_MouthOutChannel;
	OUT_.WingControllerOutC = uCHAN_WingControllerOutC;
	OUT_.WingLeftChannel = uCHAN_WingLeftChannel;
	OUT_.WingRightChannel = uCHAN_WingRightChannel;
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

unsigned char name_ControllerChannel;
unsigned char name_InitChannel;
unsigned char name_WingControllerInC;

	/* Calling Input Functions */

IN_.ControllerChannel(name_ControllerChannel);
IN_.InitChannel(name_InitChannel);
IN_.WingControllerInC(name_WingControllerInC);


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
	End of CIP Connector Template Module for CIP SHELL sBoesewicht
*********************************************************************/