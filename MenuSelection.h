// MenuSelection.h

#ifndef _MENUSELECTION_h
#define _MENUSELECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "StickHardware.h"
#include "BaseEffectSetup.h"
#include "RGBController.h"
#include "ConfigurationManager.h"

extern uint8_t arial_bold[];

class MenuSelection
{
private:
	StickHardware m_hardware;
	BaseEffectSetup **m_processors;
	ConfigurationManager *m_configuration_manager;

	uint32_t m_previous_button;
	uint32_t m_select_button;
	uint32_t m_next_button;
	uint32_t m_setup_button;

	uint32_t m_total_processors = 0;

	void initialise_mode_selection_menu();
	void set_selected_processor(int selected_mode);

public:
	MenuSelection(StickHardware hardware, BaseEffectSetup **processors, int num_processors, ConfigurationManager *configuration_manager);
	void run();
};

#endif

