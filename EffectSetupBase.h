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

#ifndef _EFFECTSETUPBASE_h
#define _EFFECTSETUPBASE_h

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

class EffectSetupBase
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
	EffectSetupBase(StickHardware hardware, PaintingStateMachine *state_machine);
	virtual String name() = 0;
	virtual void engage() = 0;
};


#endif

