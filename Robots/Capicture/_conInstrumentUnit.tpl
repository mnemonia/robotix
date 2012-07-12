
/*********************************************************************
	SYSTEM Instrument
	IMPLEMENTATION InstrumentImpl
	CIP Connector Template Module for CIP SHELL sInstrumentUnit
	Filename: _conInstrumentUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		July 12, 2012  9:11:09 pm
	activated code options:
		'unsigned char' for 'enum'
		C-code
*********************************************************************/

/* Include Files */

#include "sInstrumentUnit.h"


/*********************************************************************
	User defined Output Channel Functions
*********************************************************************/

/* Output Channel Functions,
	called by CIP Machine when a Message is written.
	User defined function, with name to consider as suggestion */

/* Parameters
	name_		name value of message */

void uCHAN_E_OutChannel (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_NO_TONE:
		/* user defined code */
		break;
	case C2_TONE:
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

	OUT_.E_OutChannel = uCHAN_E_OutChannel;
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

unsigned char name_E_InChannel;

	/* Calling Input Functions */

IN_.E_InChannel(name_E_InChannel);


/* Trigger Function Calls */

TRG_.TICK_();		/* increment CIP Machine time by one Tick */

TRG_.STEP_();		/* perform one step, if any transition (in priority order chain, timeup, local message, auto) is pending */

TRG_.CHAIN_();		/* perform one chain, if any chain is pending */

TRG_.TIMEUP_();		/* perform one timeup, if any timeup is pending  */

TRG_.READ_();		/* perform one local read, if any local message is buffered */

TRG_.AUTO_();		/* perform one auto, if any auto is pending */

/*********************************************************************
	End of CIP Connector Template Module for CIP SHELL sInstrumentUnit
*********************************************************************/