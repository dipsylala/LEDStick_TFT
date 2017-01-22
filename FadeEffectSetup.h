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

#ifndef _FadeEffectSetup_h
#define _FadeEffectSetup_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EffectSetupBase.h"
#include "PaintingState.h"
#include "FadeConfiguration.h"
#include "FadeBase.h"
#include "FadeEffect.h"

class FadeEffectSetup : public EffectSetupBase, FadeBase
{
private:
	typedef struct
	{
		uint32_t slower_button;
		uint32_t faster_button;
		uint32_t steps_minus;
		uint32_t steps_plus;
		uint32_t previous_config;
		uint32_t next_config;
		uint32_t back_button;
		uint32_t go_button;
	} FadeSelectionButtons;

	FadeSelectionButtons m_fade_selection_buttons;
	FadeEffect *m_effect;

	int read_fades_from_source(FadeConfiguration **fade_configuration);
	void initialise_main_interface(FadeSelectionButtons &buttons);
	void set_selected_configuration(FadeConfiguration &fade_configuration);
	void show_current_delay(uint32_t delay);
	void show_current_steps(uint32_t steps);
	void setup_loop();

public:
	String name();
	void engage();
	FadeEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, FadeEffect *effect);
	void loop();
};


#endif

