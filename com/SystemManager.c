/*
  	Author: Brian Carrigan
  	Date: 4/29/2013
  	Email: brian.c.carrigan@gmail.com
 
	This file is part of the EDL8F Framework.

    The EDL8F Framework is free software: you can redistribute it and/or 
	modify it under the terms of the GNU General Public License as published 
	by the Free Software Foundation, either version 3 of the License, or 
	(at your option) any later version.

    The EDL8F Framework is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
	Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the EDL8F Framework.  If not, see <http://www.gnu.org/licenses/>
 */

#include "LPC8xx.h"
#include "EDL8F_types.h"
#include "EDL8F_WKT.h"
#include "SystemManager.h"

///////////////////////////////////////////////////////////////////////////////
//								Flag Defines								 //
///////////////////////////////////////////////////////////////////////////////
unsigned int		mConfiguredFlags;
#define FLAG_WKT	0x00000001

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
	mWKT.periodInTicks = pPeriod*10;
	
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
		mWKT.periodInTicks = pPeriod*10;
		
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
