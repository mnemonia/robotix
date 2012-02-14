
/*********************************************************************
	SYSTEM Fhotibot
	IMPLEMENTATION Arduino
	CIP Connector Template Module for CIP SHELL sTheUnit
	Filename: _conTheUnit.tpl
	generated by CIP Tool(R) Version 4.41.00
		February 15, 2012  12:14:03 am
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

void uCHAN_AutonomousDriveEvents (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C8_Attention:
		/* user defined code */
		break;
	case C8_Clear:
		/* user defined code */
		break;
	case C8_Danger:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_LeftMotor (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C4_Backward:
		/* user defined code */
		break;
	case C4_Forward:
		/* user defined code */
		break;
	case C4_Stop:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_ObstacleEvents (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C9_AvoidingObstacle:
		/* user defined code */
		break;
	case C9_ClearOfObstacles:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_RemoteControlEvents (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C7_Backward:
		/* user defined code */
		break;
	case C7_Forward:
		/* user defined code */
		break;
	case C7_Left:
		/* user defined code */
		break;
	case C7_Right:
		/* user defined code */
		break;
	case C7_Stop:
		/* user defined code */
		break;
	default: 
		break;
	}
}

void uCHAN_RightMotor (unsigned char name_)
{
	/* Accessing MESSAGE */
	switch (name_)
	{
	case C5_Backward:
		/* user defined code */
		break;
	case C5_Forward:
		/* user defined code */
		break;
	case C5_Stop:
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

	OUT_.AutonomousDriveEvents = uCHAN_AutonomousDriveEvents;
	OUT_.LeftMotor = uCHAN_LeftMotor;
	OUT_.ObstacleEvents = uCHAN_ObstacleEvents;
	OUT_.RemoteControlEvents = uCHAN_RemoteControlEvents;
	OUT_.RightMotor = uCHAN_RightMotor;
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

unsigned char name_AutonomousDriveEvents;
unsigned char name_Direction;
unsigned char name_ObstacleEvents;
unsigned char name_RemoteControlEvents;

	/* Calling Input Functions */

IN_.AutonomousDriveEvents(name_AutonomousDriveEvents);
IN_.Direction(name_Direction);
IN_.ObstacleEvents(name_ObstacleEvents);
IN_.RemoteControlEvents(name_RemoteControlEvents);


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
