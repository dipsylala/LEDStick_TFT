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

void StarEffectSetup::initialise_main_interface()
{
	m_hardware.pButtons->deleteAllButtons();

	m_hardware.pButtons->setTextFont(arial_bold);
	m_hardware.pTft->print(String("Gap Time"), 20, 30);
	m_star_selection_buttons.gap_time_slower = m_hardware.pButtons->addButton(220, 20, 40, 40, "a", BUTTON_SYMBOL);
	m_star_selection_buttons.gap_time_faster = m_hardware.pButtons->addButton(270, 20, 40, 40, "b", BUTTON_SYMBOL);
		
	m_hardware.pTft->print(String("Star Time"), 20, 80);
	m_star_selection_buttons.star_time_slower = m_hardware.pButtons->addButton(220, 70, 40, 40, "a", BUTTON_SYMBOL);
	m_star_selection_buttons.star_time_faster = m_hardware.pButtons->addButton(270, 70, 40, 40, "b", BUTTON_SYMBOL);

	m_star_selection_buttons.back_button = add_back_button();
	m_star_selection_buttons.go_button = add_go_button();

	m_hardware.pButtons->drawButtons();
}

void StarEffectSetup::loop()
{
	if (m_setup_engaged == false)
	{
		return;
	}

	m_effect->loop();

	int pressed_button = m_hardware.pButtons->checkButtons();
		
	if (pressed_button == m_star_selection_buttons.gap_time_slower && m_gap_time <= 480)
	{
		m_gap_time += 20;
	}

	if (pressed_button == m_star_selection_buttons.gap_time_slower && m_gap_time >= 20)
	{
		m_gap_time -= 20;
	}

	if (pressed_button == m_star_selection_buttons.star_time_faster && m_star_time <= 480)
	{
		m_star_time += 20;
	}

	if (pressed_button == m_star_selection_buttons.star_time_slower && m_star_time >= 20)
	{
		m_star_time -= 20;
	}

	if (pressed_button == m_star_selection_buttons.back_button)
	{ 
		m_setup_engaged = false;
	}

	//if (pressed_button == m_star_selection_buttons.go_button)
	//{
	//	prepare_screen_for_effect();
	//	m_effect->start_painting(gap_time, star_time);
	//	initialise_main_interface();
	//}
}

StarEffectSetup::StarEffectSetup(StickHardware hardware, 
							PaintingStateMachine *state_machine,
							StarEffect *effect) : EffectSetupBase(hardware, state_machine)
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
	initialise_main_interface();
}