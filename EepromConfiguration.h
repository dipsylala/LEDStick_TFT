// EepromConfiguration.h

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

