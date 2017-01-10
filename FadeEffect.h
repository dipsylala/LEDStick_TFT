// FadeEffect.h

#ifndef _FADEEFFECT_h
#define _FADEEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "FadeConfiguration.h"
#include "LEDStick.h"
#include "PaintingStateMachine.h"
#include "FadeBase.h"

class FadeEffect : FadeBase
{
private:
	LEDStick *m_strip;
	PaintingStateMachine *m_state_machine;

public:
	void start_painting(FadeConfiguration &fade_configuration, uint32_t pulse_delay, uint32_t steps_between_colours);
	FadeEffect(PaintingStateMachine * state_machine, LEDStick * pStrip);
};

#endif

