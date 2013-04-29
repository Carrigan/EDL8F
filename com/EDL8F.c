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

#include "EDL8F.h"
#include "SystemManager.h"
#include "EventManager.h"
#include "system_LPC8xx.h"

#define	DATA_BUFFER_SIZE	64

///////////////////////////////////////////////////////////////////////////////
//							Function Definitions							 //
///////////////////////////////////////////////////////////////////////////////
static void QueueErrorCheck(QueueReturn_t pReturn);

///////////////////////////////////////////////////////////////////////////////
//						Event Handling Data Structures						 //
///////////////////////////////////////////////////////////////////////////////
EventQueue_t	eventQueue;
unsigned char	dataBuffer[DATA_BUFFER_SIZE];

///////////////////////////////////////////////////////////////////////////////
//									  Main									 //
///////////////////////////////////////////////////////////////////////////////
int main()
{
	unsigned char 	receiveBuffer[16];
	Event_t			receiveEvent;
	
	// Initialize the EventManager
	EventManager_init(&eventQueue, dataBuffer, DATA_BUFFER_SIZE);
	receiveEvent.dataPtr = receiveBuffer;
	
	// Initialize the SystemManager
	SystemManager_preSetup();
	
	// User defined setup
	setup();
	
	// Begin the system
	SystemManager_postSetup();

	while(1)
	{		
		// Process all events
		while(EventManager_get(&eventQueue, &receiveEvent) != QUEUE_EMPTY)
		{
			switch(receiveEvent.eventID)
			{
				case(EVENTID_WKT):
					onWkt();
					break;
				default:
					while(1);
			}
		}
		
		// Call the user's processor function
		processor();
		
		// Goodnight, sweet prince.
		__wfi();
	}
}

///////////////////////////////////////////////////////////////////////////////
//								Interrupt Handling							 //
///////////////////////////////////////////////////////////////////////////////

void WKT_IRQHandler(void)
{	
	Event_t wktEvent;
	
	// Begin the timer again
	resetWktTimer();
	
	// Queue the WKT event
	wktEvent.eventID = EVENTID_WKT;
	wktEvent.dataLength = 0;
	wktEvent.dataPtr = (unsigned char*)0;
	
	// Write the event
	QueueErrorCheck(EventManager_put(&eventQueue, &wktEvent));
}

static void QueueErrorCheck(QueueReturn_t pReturn)
{
	switch (pReturn)
	{
		case QUEUE_SUCCESS:
			return;
		default:
			while(1);
	}
}
