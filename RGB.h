// RGB.h

#ifndef _RGB_h
#define _RGB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} RGB;

#endif

