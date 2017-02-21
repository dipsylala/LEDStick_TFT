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

#include "EepromConfiguration.h"

void EepromConfiguration::assign_default_values()
{
	strncpy (loaded_data.version, CONFIG_VERSION, 3);
	loaded_data.num_pixels = 1;
	loaded_data.brightness = 255;
}

bool EepromConfiguration::same_configuration_version()
{
	return (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
		EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
		EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]);
}

ConfigurationData EepromConfiguration::read_configuration()
{
	if (same_configuration_version())
	{
		for (uint8_t t = 0; t < sizeof(ConfigurationData); t++)
		{
			*((uint8_t*)&loaded_data + t) = EEPROM.read(CONFIG_START + t);
		}
	}
	else
	{
		assign_default_values();
	}


	return loaded_data;
}

void EepromConfiguration::write_configuration(ConfigurationData &configuration_data)
{
	for (unsigned int t = 0; t < sizeof(configuration_data); t++)
	{
		EEPROM.write(CONFIG_START + t, *((uint8_t *)&configuration_data + t));
	}
}