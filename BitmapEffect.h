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

	uint16_t get_random_position(uint16_t num_pixels, Bitmap bitmap);

public:
	void start_painting(Bitmap &bitmap, uint32_t frame_delay, bool repeat, bool random_offset);
	BitmapEffect(PaintingStateMachine * state_machine, LEDStick * pStrip);
};


#endif

