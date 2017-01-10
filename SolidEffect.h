// SolidEffect.h

#ifndef _SOLIDEFFECT_h
#define _SOLIDEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "LEDStick.h"
#include "PaintingStateMachine.h"

class SolidEffect
{
private:
	LEDStick *m_strip;
	PaintingStateMachine *m_state_machine;

public:
	void start_painting(RGB &color);
	SolidEffect(PaintingStateMachine *state_machine, LEDStick *pStrip);
};

#endif

