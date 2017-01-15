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

#ifndef _STARPROCESSOR_h
#define _STARPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseEffectSetup.h"
#include "PaintingState.h"
#include "RGBController.h"
#include "StarEffect.h"

class StarEffectSetup : public EffectSetupBase
{
private:
	typedef struct
	{
		int gap_time_slower;
		int gap_time_faster;
		int star_time_slower;
		int star_time_faster;
		int back_button;
		int go_button;
	} StarSelectionButtons;

	StarSelectionButtons m_star_selection_buttons;
	StarEffect *m_effect;

	void initialise_main_interface(StarSelectionButtons &buttons);
	void setup_loop();

public:
	String name();
	void engage();
	StarEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, StarEffect *effect);
};

#endif

