// FadeConfiguration.h

#ifndef _FADECONFIGURATION_h
#define _FADECONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"

typedef struct
{
	String name;
	int num_colours;
	RGB *colour_spread;
} FadeConfiguration;

#endif

