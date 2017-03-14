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

#ifndef _CHASEEFFECTSETUP_h
#define _CHASEEFFECTSETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "EffectSetupBase.h"
#include "RGBController.h"
#include "ChaseConfiguration.h"
#include "ChaseEffect.h"

class ChaseEffectSetup : public EffectSetupBase
{
private:
	typedef struct
	{
		uint32_t slower_button;
		uint32_t faster_button;
		uint32_t smaller_partition;
		uint32_t larger_partition;
		uint32_t previous_config;
		uint32_t next_config;
		uint32_t back_button;
		uint32_t go_button;
	} ChaseSelectionButtons;

	void initialise_main_interface(ChaseSelectionButtons &buttons);
	void setup_loop () override;
	void show_current_delay(uint32_t delay);
	void show_current_partitions(uint32_t partition_size);
	void show_selected_configuration(ChaseConfiguration &chase_configuration);
	int read_chases_from_source(ChaseConfiguration **chase_configuration);
	RGBController rgbController;
	ChaseEffect *m_effect;

public:
	String name() override;
	void engage() override;
	ChaseEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, ChaseEffect *effect);
};

#endif

