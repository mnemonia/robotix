
/*********************************************************************
	SYSTEM Fhotibot2
	IMPLEMENTATION Arduino
	CIP Connector Template Module for CIP SHELL sTheUnit
	Filename: _conTheUnit.cpp
	generated by CIP Tool(R) Version 4.41.00
		February 20, 2012  9:08:36 pm
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




/*********************************************************************
	User defined Output Channel Interface Initialization Function
*********************************************************************/




/*********************************************************************
	Execution of CIP Connector Activities
*********************************************************************/


/* Input Function Calls */

	/* Referenced Input Variables (examples) */

//unsigned char name_Position;

	/* Calling Input Functions */

//IN_.Position(name_Position);


/* Trigger Function Calls */

//TRG_.TICK_();		/* increment CIP Machine time by one Tick */

//TRG_.STEP_();		/* perform one step, if any transition (in priority order chain, timeup, local message, auto) is pending */

//TRG_.CHAIN_();		/* perform one chain, if any chain is pending */

//TRG_.TIMEUP_();		/* perform one timeup, if any timeup is pending  */

//TRG_.READ_();		/* perform one local read, if any local message is buffered */

//TRG_.AUTO_();		/* perform one auto, if any auto is pending */

/*********************************************************************
	End of CIP Connector Template Module for CIP SHELL sTheUnit
*********************************************************************/
