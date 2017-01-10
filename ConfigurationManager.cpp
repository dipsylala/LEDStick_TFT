#include "ConfigurationManager.h"

void ConfigurationManager::create_user_interface(ConfigurationManagerButtons *buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pButtons->setTextFont(arial_bold);

	m_hardware.pTft->setFont(SmallFont);
	m_hardware.pTft->print("Move the  pixel", 10, 20);
	m_hardware.pTft->print("to the last LED", 10, 30);
	
	buttons->pixel_up = m_hardware.pButtons->addButton(250, 20, 40, 40, "c", BUTTON_SYMBOL);
	buttons->pixel_down = m_hardware.pButtons->addButton(250, 70, 40, 40, "d", BUTTON_SYMBOL);
	buttons->pixel_one = m_hardware.pButtons->addButton(190, 20, 50, 40, "1");
	buttons->pixel_plus_twenty = m_hardware.pButtons->addButton(190, 70, 50, 40, "+20");

	buttons->cancel_button = m_hardware.pButtons->addButton(10, 180, 120, 40, "Cancel");
	buttons->ok_button = m_hardware.pButtons->addButton(180, 180, 120, 40, "OK");

	m_hardware.pButtons->drawButtons();
}

void ConfigurationManager::display_current_pixels(uint16_t previous_pixel_index, uint16_t current_pixel_index)
{
	m_hardware.pStrip->set_pixel_color(previous_pixel_index, 0, 0, 0);
	m_hardware.pStrip->set_pixel_color(current_pixel_index, 255, 255, 255);
	m_hardware.pStrip->commit();
	
	m_hardware.pTft->setColor(0);
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->fillRect(0, 90, 170, 90 + m_hardware.pTft->getFontYsize());
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print(String(current_pixel_index + 1) + " pixel" + (current_pixel_index == 0?"":"s"), 10, 55);
}

ConfigurationData ConfigurationManager::setup_loop()
{
	EepromConfiguration configuration;
	ConfigurationData configuration_settings = configuration.read_configuration();
	ConfigurationManagerButtons buttons;
	create_user_interface(&buttons);

	boolean ok_pressed = false;
	boolean cancel_pressed = false;

	uint16_t previous_pixel_index = 0;
	uint16_t pixel_index = configuration_settings.num_pixels - 1 ;

	m_hardware.pStrip->set_stick_length(300);

	display_current_pixels(0, pixel_index);

	while (ok_pressed == false && cancel_pressed == false)
	{
		int pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == buttons.pixel_one)
		{
			previous_pixel_index = pixel_index;
			pixel_index = 0;
			display_current_pixels(previous_pixel_index, pixel_index);
		}

		if (pressed_button == buttons.pixel_down || pressed_button == buttons.pixel_up || pressed_button == buttons.pixel_plus_twenty)
		{
			if (pressed_button == buttons.pixel_down && pixel_index > 1)
			{
				previous_pixel_index = pixel_index;
				pixel_index--;
			}

			if (pressed_button == buttons.pixel_up)
			{
				previous_pixel_index = pixel_index;
				pixel_index++;
			}

			if (pressed_button == buttons.pixel_plus_twenty)
			{
				previous_pixel_index = pixel_index;
				pixel_index += 20;
			}

			display_current_pixels(previous_pixel_index, pixel_index);
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
		configuration_settings.num_pixels = pixel_index + 1;
		configuration.write_configuration(configuration_settings);
		m_hardware.pStrip->set_pixel_color(pixel_index, 0, 0, 0);
	}

	if (cancel_pressed)
	{
		m_hardware.pStrip->set_stick_length(configuration_settings.num_pixels);
	}

	return configuration_settings;
}

ConfigurationData ConfigurationManager::engage()
{
	m_hardware.pTft->clrScr();
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->setColor(255, 0, 255);
	m_hardware.pTft->print("Setup", CENTER, 0);

	return setup_loop();
}

ConfigurationManager::ConfigurationManager(StickHardware hardware)
{
	m_hardware = hardware;
}