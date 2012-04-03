
/*********************************************************************
	SYSTEM Chaot
	IMPLEMENTATION ChaotImpl
	CIP Connector Template Module for CIP SHELL sChaotUnit
	Filename: _conChaotUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		April 3, 2012  2:01:09 am
	activated code options:
		PENDING_ information
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "sChaotUnit.h"


/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_ChaoticActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C8_DETECT_HOLD:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_ControllerActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C6_DRAWED:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_IndicatorActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_INDICATE_HIGH:
		/* user defined code */
		break;
	case C5_INDICATE_LOW:
		/* user defined code */
		break;
	case C5_INDICATE_MEDIUM:
		/* user defined code */
		break;
	case C5_RESET:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_MeasureActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C3_MEASURE:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_ShakerActions (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_CENTER:
		/* user defined code */
		break;
	case C2_LEFT:
		/* user defined code */
		break;
	case C2_RIGHT:
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

	OUT_.ChaoticActions = uCHAN_ChaoticActions;
	OUT_.ControllerActions = uCHAN_ControllerActions;
	OUT_.IndicatorActions = uCHAN_IndicatorActions;
	OUT_.MeasureActions = uCHAN_MeasureActions;
	OUT_.ShakerActions = uCHAN_ShakerActions;
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

unsigned char name_ChaoticEvents;
unsigned char name_MeasureEvents;
unsigned char name_Start;

	/* Calling Input Functions */

IN_.ChaoticEvents(name_ChaoticEvents);
IN_.MeasureEvents(name_MeasureEvents);
IN_.Start(name_Start);


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
	End of CIP Connector Template Module for CIP SHELL sChaotUnit
*********************************************************************/
