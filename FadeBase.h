// FadeBase.h

#ifndef _FADEBASE_h
#define _FADEBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"

class FadeBase
{
protected:
	RGB calculate_current_colour(RGB sourceColour, RGB destinationColour, uint32_t current_step, uint32_t total_steps);
	inline int32_t GetDifference(uint32_t first, uint32_t second);
};

#endif

