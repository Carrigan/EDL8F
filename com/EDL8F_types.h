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

#ifndef EDL8F_TYPES_H
#define EDL8F_TYPES_H

typedef enum
{
	EVENTID_WKT		= 0,
} EventId_t;

typedef enum
{
	INPUT_FLOATING,
	INPUT_PULLDOWN,
	INPUT_PULLUP,
	OUTPUT_PUSHPULL,
	OUTPUT_OPENDRAIN
} PinMode_t;

typedef enum
{
	UNIT_US,
	UNIT_MS,
	UNIT_S
} TimeUnit_t;

typedef struct
{
	unsigned int 	periodInTicks;
	unsigned char	configured;
} WktTimer_t;

#endif
