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
