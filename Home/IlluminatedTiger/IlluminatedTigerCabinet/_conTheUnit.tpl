
/*********************************************************************
	SYSTEM IlluminatedTigerCabinet
	IMPLEMENTATION IlluminatedTigerCabImp
	CIP Connector Template Module for CIP SHELL sTheUnit
	Filename: _conTheUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		December 26, 2012  12:42:38 am
	activated code options:
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

void uCHAN_UpperCenterLightChan (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C2_OFF:
		/* user defined code */
		break;
	case C2_ON:
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

	OUT_.UpperCenterLightChan = uCHAN_UpperCenterLightChan;
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

unsigned char name_CommandChannel;

	/* Calling Input Functions */

IN_.CommandChannel(name_CommandChannel);


/* Trigger Function Calls */

TRG_.TICK_();		/* increment CIP Machine time by one Tick */

TRG_.STEP_();		/* perform one step, if any transition (in priority order chain, timeup, local message, auto) is pending */

TRG_.CHAIN_();		/* perform one chain, if any chain is pending */

TRG_.TIMEUP_();		/* perform one timeup, if any timeup is pending  */

TRG_.READ_();		/* perform one local read, if any local message is buffered */

TRG_.AUTO_();		/* perform one auto, if any auto is pending */

/*********************************************************************
	End of CIP Connector Template Module for CIP SHELL sTheUnit
*********************************************************************/
