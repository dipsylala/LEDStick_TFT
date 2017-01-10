#include "EepromConfiguration.h"

ConfigurationData EepromConfiguration::assign_default_values()
{
	strncpy (loaded_data.version, CONFIG_VERSION, 3);
	loaded_data.num_pixels = 1;
}

ConfigurationData EepromConfiguration::read_configuration()
{
	if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
		EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
		EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2])
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