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

#ifndef _EEPROMCONFIGURATION_h
#define _EEPROMCONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<eeprom.h>

#define CONFIG_VERSION "001"
#define CONFIG_START 32

typedef struct  {
	char version[4];
	uint16_t num_pixels;
} ConfigurationData;

class EepromConfiguration
{
private:
	ConfigurationData loaded_data;
	void assign_default_values();

public:
	ConfigurationData read_configuration();
	void write_configuration(ConfigurationData &configuration_data);
};

#endif

