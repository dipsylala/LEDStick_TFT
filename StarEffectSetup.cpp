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

#include "StarEffectSetup.h"

void StarEffectSetup::initialise_main_interface(StarSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();

	m_hardware.pButtons->setTextFont(arial_bold);
	m_hardware.pTft->print(String("Gap Time"), 20, 30);
	buttons.gap_time_slower = m_hardware.pButtons->addButton(220, 20, 40, 40, "a", BUTTON_SYMBOL);
	buttons.gap_time_faster = m_hardware.pButtons->addButton(270, 20, 40, 40, "b", BUTTON_SYMBOL);
		
	m_hardware.pTft->print(String("Star Time"), 20, 80);
	buttons.star_time_slower = m_hardware.pButtons->addButton(220, 70, 40, 40, "a", BUTTON_SYMBOL);
	buttons.star_time_faster = m_hardware.pButtons->addButton(270, 70, 40, 40, "b", BUTTON_SYMBOL);

	buttons.back_button = add_back_button();
	buttons.go_button = add_go_button();

	m_hardware.pButtons->drawButtons();
}

// Configuring the effect - may or may not include a 'preview' on the stick itself
void StarEffectSetup::setup_loop()
{
	StarSelectionButtons selection_buttons;
	int gap_time = 200;
	int star_time = 200;

	RGB starlight_color = create_rgb(255, 255, 255);

	initialise_main_interface(selection_buttons);

	int num_pixels = m_hardware.pStrip->get_stick_length();
	boolean back_pressed = false;
	
	while (back_pressed == false)
	{
		int random_pixel = random(num_pixels);

		m_hardware.pStrip->clear_strip();

		m_hardware.pStrip->set_pixel_color(random_pixel, 255, 255, 255);
		m_hardware.pStrip->commit();
		delay(star_time);

		int pressed_button = m_hardware.pButtons->checkButtons();
		
		if (pressed_button == selection_buttons.gap_time_slower && gap_time <= 480)
		{
			gap_time += 20;
		}

		if (pressed_button == selection_buttons.gap_time_slower && gap_time >= 20)
		{
			gap_time -= 20;
		}

		if (pressed_button == selection_buttons.star_time_faster && star_time <= 480)
		{
			star_time += 20;
		}

		if (pressed_button == selection_buttons.star_time_slower && star_time >= 20)
		{
			star_time -= 20;
		}

		if (pressed_button == selection_buttons.back_button)
		{ 
			back_pressed = true;
		}

		if (pressed_button == selection_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(gap_time, star_time);
			initialise_main_interface(selection_buttons);
		}

		m_hardware.pStrip->clear_strip();
		delay(gap_time);
	}
}



StarEffectSetup::StarEffectSetup(StickHardware hardware, 
							PaintingStateMachine *state_machine,
							StarEffect *effect) : BaseEffectSetup(hardware, state_machine)
{
	m_effect = effect;
}

String StarEffectSetup::name()
{
	return "Star";
}

void StarEffectSetup::engage()
{
	initialise_screen_base(String("Star mode"));
	setup_loop();
}