#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "../../com/EventManager.h"

#define EVENT_BUFFER_SIZE	8
#define DATA_BUFFER_SIZE	128

EventQueue_t	eventQueue;
Event_t			eventBuffer[EVENT_BUFFER_SIZE];
char			dataBuffer[DATA_BUFFER_SIZE];

int main()
{
	Event_t retreivedEvent;
	char inStr[50];
	char outStr[50];
	int c = 0;

	// Initialize data buffer
	EventManager_init(&eventQueue, eventBuffer, EVENT_BUFFER_SIZE, dataBuffer, DATA_BUFFER_SIZE);

	// Get the first command
	printf("Type anything to add a new event, 'pop' to retreive the last event, or 'exit' to exit.\n");
	scanf("%s", inStr);

	while(strcmp(inStr, "exit") != 0)
	{
		if(strcmp(inStr, "pop") == 0)
		{
			if(EventManager_get(&eventQueue, &retreivedEvent, outStr) != EVENT_QUEUE_EMPTY)
			{
				printf("Event %i:\n", c);
				printf("ID: %i\n", retreivedEvent.eventID);
				printf("Data Length: %i\n", retreivedEvent.eventDataLength);
				printf(">> %s\n\n", outStr);
				c++;
			} else {
				printf("Pop failed: queue empty.\n");
			}
		} else {
			Event_t currentEvent;

			currentEvent.eventID = EVENTID_UART;
			currentEvent.eventDataLength = strlen(inStr);

			switch(EventManager_put(&eventQueue, &currentEvent, inStr))
			{
				case	EVENT_QUEUE_FULL:
					printf("Failure: Event queue is full.\n");
					break;
				case	DATA_QUEUE_FULL:
					printf("Failure: Data queue is full.\n");
					break;
				default:
					printf("Success.\n");
					break;
			}
		}

		printf("Add new event, pop to retreive the last event, or exit to exit.\n");
		scanf("%s", inStr);
	}

	printf("Dumping remaining events:\n");
	printf("\n\n--------------------------------------------------------------------------\n");

	while(EventManager_get(&eventQueue, &retreivedEvent, outStr) != EVENT_QUEUE_EMPTY)
	{
		printf("Event %i:\n", c);
		printf("ID: %i\n", retreivedEvent.eventID);
		printf("Data Length: %i\n", retreivedEvent.eventDataLength);
		printf(">> %s\n\n", outStr);
		c++;
	}

	printf("--------------------------------------------------------------------------\n\n");

	printf("Exit window to exit.\n");

	while(1);
	return 0;
}
