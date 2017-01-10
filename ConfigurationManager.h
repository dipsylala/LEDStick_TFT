// ConfigurationManager.h

#ifndef _CONFIGURATIONMANAGER_h
#define _CONFIGURATIONMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "StickHardware.h"
#include "EepromConfiguration.h"

extern uint8_t arial_bold[];
extern uint8_t SmallFont[];

#define CONFIGURATION_APPLY  -1
#define CONFIGURATION_CANCEL -2

class ConfigurationManager
{
private:

	typedef struct
	{
		uint32_t cancel_button;
		uint32_t ok_button;
		uint32_t pixel_up;
		uint32_t pixel_one;
		uint32_t pixel_plus_twenty;
		uint32_t pixel_down;
	} ConfigurationManagerButtons;

	StickHardware m_hardware;

	ConfigurationData setup_loop();
	void create_user_interface(ConfigurationManagerButtons *buttons);
	void display_current_pixels(uint32_t previous_pixel_index, uint32_t current_pixel_index);

public:
	ConfigurationData engage();
	ConfigurationManager(StickHardware hardware);
};


#endif

