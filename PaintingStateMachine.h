// PaintingStateMachine.h

#ifndef _PAINTINGSTATEMACHINE_h
#define _PAINTINGSTATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "StickHardware.h"
#include "PaintingState.h"

#define EFFECT_TRIGGER 10

class PaintingStateMachine
{
private:
	PaintingState current_state;
	StickHardware m_hardware;

	bool read_state_jump();
	int current_pin_state = LOW;
	int last_button_state = LOW;
	unsigned long button_down_time;
	unsigned long last_debounce_time = 0;
	unsigned long debounce_delay = 50;

public:
	void reset();
	PaintingStateMachine(StickHardware hardware);
	PaintingState get_state();
	void set_state(PaintingState state);
};


#endif

