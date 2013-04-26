#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "EDL8F_types.h"

typedef enum
{
	QUEUE_SUCCESS,
	QUEUE_EMPTY,
	QUEUE_FULL
} QueueReturn_t;

typedef struct
{
	unsigned char	*eventBuffer;
	unsigned char 	*bufferEnd;
	unsigned char	*head;
	unsigned int	*tail;
	unsigned int	capacity;
	unsigned int	spaceLeft;
} EventQueue_t;

typedef struct
{
	EventId_t 		eventID;
	unsigned char 	dataLength; 
	unsigned char 	*dataPtr;
} Event_t;

void 			EventManager_init(EventQueue_t *pEventQueue, unsigned char *pEventBuffer, unsigned int pEventBufferSize);
QueueReturn_t	EventManager_get(EventQueue_t *pEventQueue, Event_t *pEventRead);
QueueReturn_t	EventManager_put(EventQueue_t *pEventQueue, Event_t *pEventWrite);

#endif