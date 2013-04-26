#include "LPC8xx.h"
#include "EDL8F_types.h"
#include "SystemManager.h"

///////////////////////////////////////////////////////////////////////////////
//								Flag Defines								 //
///////////////////////////////////////////////////////////////////////////////
unsigned int		mConfiguredFlags;
#DEFINE FLAG_WKT	0x00000001

///////////////////////////////////////////////////////////////////////////////
//						  System Manager State Machine						 //
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	STATE_SETUP,
	STATE_RUNNING
} SystemState_t;
SystemState_t mSystemState;

///////////////////////////////////////////////////////////////////////////////
//							Peripheral Structures							 //
///////////////////////////////////////////////////////////////////////////////
WktTimer_t	mWKT;

///////////////////////////////////////////////////////////////////////////////
//							   System Functions								 //
///////////////////////////////////////////////////////////////////////////////

void 	SystemManager_preSetup()
{
	// Set all peripherals to initially UNCONFIGURED
	mWKT.configured = 0;
	
	// Set the state to SETUP
	mSystemState = STATE_SETUP;
}

void 	SystemManager_postSetup()
{
	// Go through all peripherals and begin anything that needs beginning
	if(mConfiguredFlags & FLAG_WKT)
	{
		wkt_begin(mWKT.periodInTicks);
	}	
	
	// Beginning the program, set the state to RUNNING:
	mSystemState = STATE_RUNNING;
}


///////////////////////////////////////////////////////////////////////////////
//							User Facing Functions							 //
///////////////////////////////////////////////////////////////////////////////

void setupWktTimer(unsigned int pPeriod)
{
	// Save the period
	mWKT.periodInUnits = pPeriod*10;
	
	// Set as configured
	mWKT.configured = 1;
}

void resetWktTimer()
{
	// Clear the interrupt flag.
	LPC_WKT->CTRL |= 0x00000002;
	
	// Start the timer again:
	wkt_begin(mWKT.periodInTicks);
}

void changeWktTimer(unsigned int pPeriod)
{
	// If we aren't configured, ignore it.
	if(mWKT.configured == 0)
	{
		// Stop WKT if its running
		wkt_stop();
		
		// Set the new period
		mWKT.periodInUnits = pPeriod*10;
		
		// If we are running, begin the timer again
		if(mSystemState == STATE_RUNNING)
		{
			wkt_begin(mWKT.periodInTicks);
		}
	}
}

void stopWktTimer()
{
	mWKT.configured = 0;
	wkt_stop();
}