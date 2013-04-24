#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <stdint.h>

typedef enum
{
	EVENTID_TIMER,
	EVENTID_UART
} EventId_t;

typedef enum
{
	QUEUE_SUCCESS,
	EVENT_QUEUE_EMPTY,
	EVENT_QUEUE_FULL,
	DATA_QUEUE_EMPTY,
	DATA_QUEUE_FULL
} QueueReturn_t;

typedef struct
{
	EventId_t 	eventID;
	unsigned int	eventDataLength;
} Event_t;

typedef struct
{
	char			*dataBuffer;
	char			writeIndex;
	char			readIndex;
	unsigned int	capacity;
	unsigned int	spaceLeft;
} DataQueue_t;

typedef struct
{
	Event_t			*eventBuffer;
	unsigned int	writeIndex;
	unsigned int	readIndex;
	unsigned int	capacity;
	unsigned int	spaceLeft;
	size_t			entrySize;
	DataQueue_t		dataQueue;
} EventQueue_t;

void 			EventManager_init(EventQueue_t *pEventQueue, Event_t *pEventBuffer, unsigned int pEventBufferSize, char *pDataBuffer, unsigned int pDataBufferSize);
QueueReturn_t	EventManager_get(EventQueue_t *pEventQueue, Event_t *pEventRead, char *pDataRead);
QueueReturn_t	EventManager_put(EventQueue_t *pEventQueue, Event_t *pEventWrite, char *pDataWrite);

#endif
