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

#include "GammaConfigurationManager.h"

void GammaConfigurationManager::create_user_interface(GammaConfigurationManagerButtons *buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pButtons->setTextFont(arial_bold);

	buttons->gamma_down = m_hardware.pButtons->addButton(220, 20, 40, 40, "a", BUTTON_SYMBOL);
	buttons->gamma_up = m_hardware.pButtons->addButton(270, 20, 40, 40, "b", BUTTON_SYMBOL);

	buttons->cancel_button = m_hardware.pButtons->addButton(10, 180, 120, 40, "Cancel");
	buttons->ok_button = m_hardware.pButtons->addButton(180, 180, 120, 40, "OK");

	m_hardware.pButtons->drawButtons();
}

void GammaConfigurationManager::display_current_gamma(float gamma)
{
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->print("Gamma: " + String(gamma), 20, 30);
	m_hardware.pStrip->set_stick_gamma(gamma);
}

ConfigurationData GammaConfigurationManager::setup_loop()
{
	EepromConfiguration configuration;
	ConfigurationData configuration_settings = configuration.read_configuration();
	GammaConfigurationManagerButtons buttons;
	create_user_interface(&buttons);

	boolean ok_pressed = false;
	boolean cancel_pressed = false;

	float gamma = configuration_settings.gamma_level;

	display_current_gamma(gamma);

	while (ok_pressed == false && cancel_pressed == false)
	{
		int pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == buttons.gamma_down || pressed_button == buttons.gamma_up)
		{
			if (pressed_button == buttons.gamma_down && gamma > 1.1)
			{
				gamma = gamma - 0.1;
			}

			if (pressed_button == buttons.gamma_up && gamma < 5)
			{
				gamma = gamma + 0.1;
			}

			m_hardware.pStrip->set_stick_gamma(gamma);

			display_current_gamma(gamma);
		}

		if (pressed_button == buttons.cancel_button)
		{
			cancel_pressed = true;
		}

		if (pressed_button == buttons.ok_button)
		{
			ok_pressed = true;
		}
	}

	if (ok_pressed)
	{
		configuration_settings.gamma_level = gamma;
		configuration.write_configuration(configuration_settings);
	}

	if (cancel_pressed)
	{
		m_hardware.pStrip->set_stick_brightness(configuration_settings.brightness);
	}

	return configuration_settings;
}

ConfigurationData GammaConfigurationManager::engage()
{
	m_hardware.pTft->clrScr();
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->setColor(255, 0, 255);
	m_hardware.pTft->print("Gamma Setup", CENTER, 0);

	return setup_loop();
}

GammaConfigurationManager::GammaConfigurationManager(StickHardware hardware)
{
	m_hardware = hardware;
}