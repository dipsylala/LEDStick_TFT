// BitmapEffect.h

#ifndef _BITMAPEFFECT_h
#define _BITMAPEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "Bitmap.h"
#include "PaintingStateMachine.h"

class BitmapEffect
{
private:
	LEDStick *m_strip;
	PaintingStateMachine *m_state_machine;

public:
	void start_painting(Bitmap &bitmap, uint32_t frame_delay, bool repeat);
	BitmapEffect(PaintingStateMachine * state_machine, LEDStick * pStrip);
};


#endif

