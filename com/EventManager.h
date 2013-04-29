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
	unsigned char	*tail;
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
