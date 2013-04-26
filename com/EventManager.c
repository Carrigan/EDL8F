#include "EventManager.h"

void EventManager_init(EventQueue_t *pEventQueue, unsigned char *pEventBuffer, unsigned int pEventBufferSize)
{
	pEventQueue->eventBuffer = pEventBuffer;
	pEventQueue->bufferEnd = pEventBuffer + pEventBufferSize;
	pEventQueue->head = pEventBuffer;
	pEventQueue->tail = pEventBuffer;
	pEventQueue->capacity = pEventBufferSize;
	pEventQueue->spaceLeft = pEventBufferSize;
}

QueueReturn_t	EventManager_get(EventQueue_t *pEventQueue, Event_t *pEventRead)
{
	unsigned int i = 0;
	unsigned char *currentPtr = pEventRead->dataPtr;
	
	if(pEventQueue -> spaceLeft == pEventQueue -> capacity)
	{
		return QUEUE_EMPTY;
	}
	
	// Get the ID
	pEventRead -> eventID = (EventId_t)(*(pEventQueue -> tail));
	
	// Increment read pointer
	pEventQueue -> tail++;
	if(pEventQueue -> tail == pEventQueue -> bufferEnd)
		pEventQueue -> tail = pEventQueue -> eventBuffer;
	
	// Get the length
	pEventRead -> dataLength = *(pEventQueue -> tail);
	
	// Increment read pointer
	pEventQueue -> tail++;
	if(pEventQueue -> tail == pEventQueue -> bufferEnd)
		pEventQueue -> tail = pEventQueue -> eventBuffer;
	
	for(; i < pEventRead -> dataLength; i++)
	{
		// Get next data byte
		*currentPtr = *(pEventQueue -> tail);
		
		// Increment the write pointer
		currentPtr++;
		
		// Increment read pointer
		pEventQueue -> tail++;
		if(pEventQueue -> tail == pEventQueue -> bufferEnd)
			pEventQueue -> tail = pEventQueue -> eventBuffer;	
	}
	
	// Fix space left
	pEventQueue -> spaceLeft += (pEventRead -> dataLength + 2);

	// AOK	
	return QUEUE_SUCCESS;
}


QueueReturn_t	EventManager_put(EventQueue_t *pEventQueue, Event_t *pEventWrite)
{
	unsigned int i = 0;
	unsigned char *currentPtr = pEventWrite->dataPtr;
	
	if(pEventQueue -> spaceLeft < (pEventWrite->dataLength + 2))
	{
		return QUEUE_FULL;
	}
	
	// Write the ID First
	*(pEventQueue -> head) = (unsigned char)(pEventWrite -> eventID);
	
	// Increment write pointer
	pEventQueue -> head++;
	if(pEventQueue -> head == pEventQueue -> bufferEnd)
		pEventQueue -> head = pEventQueue -> eventBuffer;
	
	// Write the length next
	*(pEventQueue -> head) = pEventWrite -> dataLength;
	
	// Increment write pointer
	pEventQueue -> head++;
	if(pEventQueue -> head == pEventQueue -> bufferEnd)
		pEventQueue -> head = pEventQueue -> eventBuffer;	

	// Write the data
	for(; i < pEventWrite->dataLength; i++)
	{
		// Write a byte of data
		*(pEventQueue -> head) = *currentPtr;
		
		// Advance the read pointer
		currentPtr++;
	
		// Increment write pointer
		pEventQueue -> head++;
		if(pEventQueue -> head == pEventQueue -> bufferEnd)
			pEventQueue -> head = pEventQueue -> eventBuffer;	
	}
	
	// Fix space left
	pEventQueue -> spaceLeft -= (pEventWrite -> dataLength + 2);
	
	// AOK
	return QUEUE_SUCCESS;
}