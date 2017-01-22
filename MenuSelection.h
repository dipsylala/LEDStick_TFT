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

#ifndef _MENUSELECTION_h
#define _MENUSELECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "StickHardware.h"
#include "EffectSetupBase.h"
#include "RGBController.h"
#include "ConfigurationManager.h"

extern uint8_t arial_bold[];

class MenuSelection
{
private:
	StickHardware m_hardware;
	EffectSetupBase **m_effect_setups;
	ConfigurationManager *m_configuration_manager;

	uint32_t m_previous_button;
	uint32_t m_select_button;
	uint32_t m_next_button;
	uint32_t m_setup_button;

	uint32_t m_total_effects = 0;
	uint32_t m_current_mode_index = 0;

	void initialise_mode_selection_menu();
	void set_selected_processor(uint32_t selected_mode);

public:
	MenuSelection(StickHardware hardware, EffectSetupBase **effects, int num_effects, ConfigurationManager *configuration_manager);
	void run();
	void loop();
};

#endif

