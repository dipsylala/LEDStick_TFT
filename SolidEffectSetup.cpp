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

#include "SolidEffectSetup.h"

void SolidEffectSetup::initialise_main_interface(SolidSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	buttons.back_button = add_back_button();
	buttons.go_button = buttons.go_button = add_go_button();

	rgbController.create_interface_components(m_hardware, 40, 20);

	m_hardware.pButtons->drawButtons();
}

// Configuring the effect - may or may not include a 'preview' on the stick itself
void SolidEffectSetup::setup_loop()
{
	SolidSelectionButtons main_buttons;
	initialise_main_interface(main_buttons);

	boolean back_pressed = false;
	LEDRGB current_color = create_rgb(128, 128, 128);
	boolean has_changed = true;
	boolean led_on = true;

	while (back_pressed == false)
	{
		if (has_changed)
		{
			m_hardware.pStrip->set_total_strip_colour(current_color);
		}

		if (!m_hardware.pTouch->dataAvailable())
		{
			continue;
		}

		m_hardware.pTouch->read();

		int16_t x = m_hardware.pTouch->getX();
		int16_t y = m_hardware.pTouch->getY();

		int pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == main_buttons.back_button)
		{
			back_pressed = true;
		}

		if (pressed_button == main_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(current_color);
			initialise_main_interface(main_buttons);
		}

		rgbController.check_point(x, y, current_color, has_changed);
	}
}

SolidEffectSetup::SolidEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, SolidEffect *effect) : EffectSetupBase(hardware, state_machine)
{
	m_effect = effect;
}

String SolidEffectSetup::name()
{
	return "Solid";
}

void SolidEffectSetup::engage()
{
	initialise_screen_base(String ("Solid mode"));
	setup_loop();
}