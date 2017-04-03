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

#ifndef _GAMMACONFIGURATIONMANAGER_h
#define _GAMMACONFIGURATIONMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "StickHardware.h"
#include "EepromConfiguration.h"

extern uint8_t arial_bold[];
extern uint8_t SmallFont[];

class GammaConfigurationManager
{
private:

	typedef struct
	{
		uint16_t cancel_button;
		uint16_t ok_button;
		uint16_t gamma_down;
		uint16_t gamma_up;
	} GammaConfigurationManagerButtons;

	StickHardware m_hardware;

	ConfigurationData setup_loop();
	void create_user_interface(GammaConfigurationManagerButtons *buttons);
	void display_current_gamma(float gamma);

public:
	ConfigurationData engage();
	GammaConfigurationManager(StickHardware hardware);
};


#endif

