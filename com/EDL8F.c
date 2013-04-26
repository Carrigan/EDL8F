#include "EDL8F.h"
#include "SystemManager.h"
#include "EventManager.h"

#define EVENT_BUFFER_SIZE	8
#define	DATA_BUFFER_SIZE	64

///////////////////////////////////////////////////////////////////////////////
//							Function Definitions							 //
///////////////////////////////////////////////////////////////////////////////
static void QueueErrorCheck(QueueReturn_t pReturn);

///////////////////////////////////////////////////////////////////////////////
//						Event Handling Data Structures						 //
///////////////////////////////////////////////////////////////////////////////
EventQueue_t	eventQueue;
Event_t			eventBuffer[EVENT_BUFFER_SIZE];
unsigned char	dataBuffer[DATA_BUFFER_SIZE];

///////////////////////////////////////////////////////////////////////////////
//									  Main									 //
///////////////////////////////////////////////////////////////////////////////
int main()
{
	unsigned char 	receiveBuffer[16];
	Event_t			receiveEvent;
	
	// Initialize the EventManager
	EventManager_init(&eventQueue, eventBuffer, EVENT_BUFFER_SIZE, dataBuffer, DATA_BUFFER_SIZE);
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
		while(EventManager_get(&eventQueue, &receiveEvent) != EVENT_QUEUE_EMPTY)
		{
			switch(receiveEvent.eventID)
			{
				case(EVENTID_WKT):
					onWkt();
					break;
				default:
					while(1);
					break;
			}
		}
	
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
	QueueErrorCheck(EventManager_put(&eventBuffer, &wktEvent);
}

static void QueueErrorCheck(QueueReturn_t pReturn)
{
	switch (pReturn)
	{
		case QUEUE_SUCCESS:
			return;
		default:
			while(1);
			break;
	}
}
