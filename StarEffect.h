// StarEffect.h

#ifndef _STAREFFECT_h
#define _STAREFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "LEDStick.h"
#include "PaintingStateMachine.h"

class StarEffect
{
private:
	LEDStick *m_strip;
	PaintingStateMachine *m_state_machine;

public:
	void start_painting(int gap_time, int star_time_slower);
	StarEffect(PaintingStateMachine * state_machine, LEDStick *pStrip);
};

#endif

