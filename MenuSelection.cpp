#include "MenuSelection.h"

MenuSelection::MenuSelection(StickHardware hardware, BaseEffectSetup **processors, int num_processors, ConfigurationManager *configuration_manager)
{
	m_hardware = hardware;
	m_processors = processors;
	m_total_processors = num_processors;
	m_configuration_manager = configuration_manager;
}

void MenuSelection::initialise_mode_selection_menu()
{
	m_hardware.pTft->clrScr();
	m_hardware.pTft->setColor(255, 0, 255);

	m_hardware.pButtons->deleteAllButtons();
	m_hardware.pButtons->setTextFont(arial_bold);
	m_setup_button = m_hardware.pButtons->addButton(10, 10, 80, 60, "s", BUTTON_SYMBOL);
	m_select_button = m_hardware.pButtons->addButton(10, 90, 300, 60, "");
	m_previous_button = m_hardware.pButtons->addButton(220, 180, 40, 40, "a", BUTTON_SYMBOL);
	m_next_button = m_hardware.pButtons->addButton(270, 180, 40, 40, "b", BUTTON_SYMBOL);
	m_hardware.pButtons->drawButtons();

	m_hardware.pStrip->clear_strip();
}

void MenuSelection::set_selected_processor(int selected_mode)
{
	char nameBuf[50];
	m_processors[selected_mode]->name().toCharArray(nameBuf, 50);
	m_hardware.pButtons->relabelButton(m_select_button, nameBuf, true);
	m_hardware.pButtons->drawButton(m_select_button);
}


void MenuSelection::run()
{
	int selected_processor_index = 0;

	m_hardware.pTft->clrScr();

	initialise_mode_selection_menu();

	set_selected_processor(0);

	bool back_pressed = false;

	while (back_pressed == false)
	{
		if (m_hardware.pTouch->dataAvailable() == false)
		{
			continue;
		}

		int pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == m_previous_button || pressed_button == m_next_button )
		{
			if (pressed_button == m_previous_button)
			{
				if (selected_processor_index > 0)
				{
					selected_processor_index--;
				}
				else
				{
					selected_processor_index = m_total_processors - 1;
				}
			}

			if (pressed_button == m_next_button)
			{
				if (selected_processor_index < m_total_processors - 1)
				{
					selected_processor_index++;
				}
				else
				{
					selected_processor_index = 0;
				}
			}

			set_selected_processor(selected_processor_index);
		}

		if (pressed_button == m_setup_button)
		{
			ConfigurationData config_data = m_configuration_manager->engage();
			initialise_mode_selection_menu();
			set_selected_processor(selected_processor_index);
			m_hardware.pStrip->set_stick_length(config_data.num_pixels);
		}

		if (pressed_button == m_select_button)
		{
			m_processors[selected_processor_index]->engage();
			initialise_mode_selection_menu();
			set_selected_processor(selected_processor_index);
		}

		while (m_hardware.pTouch->dataAvailable() == true) {};
	}
}
