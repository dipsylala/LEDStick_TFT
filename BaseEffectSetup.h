// BaseProcessor.h

#ifndef _BASEPROCESSOR_h
#define _BASEPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "PaintingStateMachine.h"
#include "StickHardware.h"

extern uint8_t SmallFont[];
extern uint8_t arial_bold[];

class BaseEffectSetup
{
protected:

	StickHardware m_hardware;
	PaintingStateMachine *m_state_machine;

	void clear_space(int x1, int y1, int x2, int y2);
	void initialise_screen_base(String title);
	RGB create_rgb(uint8_t red, uint8_t green, uint8_t blue);
	int add_go_button();
	int add_back_button();
	void prepare_screen_for_effect();

	virtual void setup_loop() = 0;

public:
	BaseEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine);
	virtual String name() = 0;
	virtual void engage() = 0;
};


#endif

