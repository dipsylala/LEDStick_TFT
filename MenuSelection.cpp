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

#include "MenuSelection.h"

MenuSelection::MenuSelection(StickHardware hardware, EffectSetupBase **effects, int num_effects, ConfigurationManager *configuration_manager)
{
	m_hardware = hardware;
	m_effect_setups = effects;
	m_total_effects = num_effects;
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

void MenuSelection::set_selected_processor(uint32_t selected_mode)
{
	char nameBuf[50];
	m_effect_setups[selected_mode]->name().toCharArray(nameBuf, 50);
	m_hardware.pButtons->relabelButton(m_select_button, nameBuf, true);
	m_hardware.pButtons->drawButton(m_select_button);

	m_current_mode_index = selected_mode;
}


void MenuSelection::run()
{
	int selected_processor_index = 0;

	m_hardware.pTft->clrScr();

	initialise_mode_selection_menu();

	set_selected_processor(0);
}

void MenuSelection::loop()
{
	Serial.println("In MenuSelection loop");

	if (m_hardware.pTouch->dataAvailable() == false)
	{
		return;
	}

	Serial.println("In the loop");

	int pressed_button = m_hardware.pButtons->checkButtons();

	if (pressed_button == m_previous_button || pressed_button == m_next_button )
	{
		if (pressed_button == m_previous_button)
		{
			if (m_current_mode_index > 0)
			{
				m_current_mode_index--;
			}
			else
			{
				m_current_mode_index = m_total_effects - 1;
			}
		}

		if (pressed_button == m_next_button)
		{
			if (m_current_mode_index < m_total_effects - 1)
			{
				m_current_mode_index++;
			}
			else
			{
				m_current_mode_index = 0;
			}
		}

		set_selected_processor(m_current_mode_index);
	}

	if (pressed_button == m_setup_button)
	{
		ConfigurationData config_data = m_configuration_manager->engage();
		initialise_mode_selection_menu();
		m_hardware.pStrip->set_stick_length(config_data.num_pixels);

		set_selected_processor(m_current_mode_index);
	}

	if (pressed_button == m_select_button)
	{
		m_effect_setups[m_current_mode_index]->engage();
		initialise_mode_selection_menu();
		set_selected_processor(m_current_mode_index);
	}

	while (m_hardware.pTouch->dataAvailable() == true) {};
}


