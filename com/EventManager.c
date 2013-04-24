#include <string.h>
#include "EventManager.h"
#include <stdint.h>

#define DEBUG

void EventManager_init(EventQueue_t *pEventQueue, Event_t *pEventBuffer, unsigned int pEventBufferSize, char *pDataBuffer, unsigned int pDataBufferSize)
{
	// Initialize the event manager
	pEventQueue -> capacity = pEventBufferSize;
	pEventQueue -> spaceLeft = pEventBufferSize;
	pEventQueue -> eventBuffer = pEventBuffer;
	pEventQueue -> writeIndex = 0;
	pEventQueue -> readIndex = 0;
	pEventQueue -> entrySize = sizeof(Event_t);

	// Initialize the data queue
	pEventQueue -> dataQueue.readIndex = 0;
	pEventQueue -> dataQueue.writeIndex = 0;
	pEventQueue -> dataQueue.dataBuffer = pDataBuffer;
	pEventQueue -> dataQueue.spaceLeft = pDataBufferSize;
	pEventQueue -> dataQueue.capacity = pDataBufferSize;
}

QueueReturn_t	EventManager_get(EventQueue_t *pEventQueue, Event_t *pEventRead, char *pDataRead)
{
	unsigned int i = 0;

	if(pEventQueue->spaceLeft == pEventQueue -> capacity)
	{
		return EVENT_QUEUE_EMPTY;
	}
	
	// Copy the event.
	memcpy(pEventRead, &pEventQueue->eventBuffer[pEventQueue -> readIndex], pEventQueue->entrySize);

	// Copy the data.
	for(i; i < pEventRead->eventDataLength; i++)
	{
		pDataRead[i] = pEventQueue->dataQueue.dataBuffer[pEventQueue->dataQueue.readIndex];
		pEventQueue->dataQueue.readIndex++;
		if(pEventQueue->dataQueue.readIndex == pEventQueue->dataQueue.capacity)
		{
			pEventQueue -> dataQueue.readIndex = 0;
		}
		pEventQueue->dataQueue.spaceLeft++;
	}

	// Advance the Event tail.
	pEventQueue->readIndex++;
	if(pEventQueue->readIndex == pEventQueue -> capacity)
	{
		pEventQueue->readIndex = 0;
	}	

	// We have more space now.
	pEventQueue -> spaceLeft++;

	// Return that our write was successful.
	return QUEUE_SUCCESS;
}

QueueReturn_t	EventManager_put(EventQueue_t *pEventQueue, Event_t *pEventWrite, char *pDataWrite)
{
	unsigned int i = 0;
	
	// If theres no event room left, kick back an error.
	if(pEventQueue->spaceLeft == 0)
	{
		return EVENT_QUEUE_FULL;
	}
	
	// If theres no data room left, error also.
	if(pEventQueue->dataQueue.spaceLeft < pEventWrite->eventDataLength)
	{
		return DATA_QUEUE_FULL;
	}
	
	// Copy over the event.
	memcpy(&pEventQueue->eventBuffer[pEventQueue -> writeIndex], pEventWrite, pEventQueue->entrySize);

	// Copy over the data.
	for(i; i < pEventWrite->eventDataLength; i++)
	{
		pEventQueue->dataQueue.dataBuffer[pEventQueue->dataQueue.writeIndex] = pDataWrite[i];
		pEventQueue->dataQueue.writeIndex++;
		if(pEventQueue->dataQueue.writeIndex == pEventQueue->dataQueue.capacity)
		{
			pEventQueue->dataQueue.writeIndex = 0;
		}
		pEventQueue->dataQueue.spaceLeft--;
	}

#ifdef DEBUG
	// DEBUG ONLY!!! Adds an extra 0 for printfs
	pEventQueue -> eventBuffer[pEventQueue -> writeIndex].eventDataLength++;
	pEventQueue->dataQueue.dataBuffer[pEventQueue->dataQueue.writeIndex] = 0;
	pEventQueue->dataQueue.writeIndex++;
	if(pEventQueue->dataQueue.writeIndex == pEventQueue->dataQueue.capacity)
	{
		pEventQueue->dataQueue.writeIndex = 0;
	}
	pEventQueue->dataQueue.spaceLeft--;
#endif	

	// Advance the Event head.
	pEventQueue->writeIndex++;
	if(pEventQueue->writeIndex == pEventQueue -> capacity)
	{
		pEventQueue->writeIndex = 0;
	}	

	// We have less space now.
	pEventQueue->spaceLeft--;

	// Return that our write was successful.
	return QUEUE_SUCCESS;
}
