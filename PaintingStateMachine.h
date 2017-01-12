// This file is part of LEDStick_TFT.
// 
// LEDStick_TFT is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// LEDStick_TFT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with LEDStick_TFT.If not, see <http://www.gnu.org/licenses/>.

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

