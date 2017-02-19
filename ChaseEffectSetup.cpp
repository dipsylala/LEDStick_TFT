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

#include "ChaseEffectSetup.h"

void ChaseEffectSetup::initialise_main_interface(ChaseSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();

	m_hardware.pButtons->setTextFont(arial_bold);
	buttons.slower_button = m_hardware.pButtons->addButton(220, 20, 40, 40, "a", BUTTON_SYMBOL);
	buttons.faster_button = m_hardware.pButtons->addButton(270, 20, 40, 40, "b", BUTTON_SYMBOL);

	buttons.smaller_partition = m_hardware.pButtons->addButton(220, 70, 40, 40, "a", BUTTON_SYMBOL);
	buttons.larger_partition = m_hardware.pButtons->addButton(270, 70, 40, 40, "b", BUTTON_SYMBOL);

	buttons.go_button = add_go_button();

	buttons.back_button = add_back_button();

	m_hardware.pButtons->drawButtons();
}

void ChaseEffectSetup::show_current_delay(uint32_t delay)
{
	m_hardware.pTft->setFont(arial_bold);

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print("Speed: " + String((200 - delay) / 2) + "% ", 20, 30);
}

void ChaseEffectSetup::show_current_partitions(uint32_t partition_size)
{
	m_hardware.pTft->setFont(arial_bold);

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print("Steps: " + String(partition_size), 20, 80);
}

// Configuring the effect - may or may not include a 'preview' on the stick itself
void ChaseEffectSetup::setup_loop()
{
	ChaseSelectionButtons main_buttons;
	RGB current_color = create_rgb(255, 255, 255);
	uint32_t pulse_delay = 150;
	boolean back_pressed = false;
	uint32_t total_leds = m_hardware.pStrip->get_stick_length();

	uint32_t number_of_partitions = 6;
	uint32_t size_of_partition = total_leds / number_of_partitions;

	initialise_main_interface(main_buttons);

	uint32_t current_partition_index = 0;

	show_current_partitions(number_of_partitions);
	show_current_delay(pulse_delay);

	while (back_pressed == false)
	{
		if (current_partition_index == number_of_partitions - 1)
		{
			current_partition_index = 0;
		}
		else
		{
			current_partition_index++;
		}

		m_hardware.pStrip->clear_strip(false);

		uint32_t current_position = (size_of_partition * current_partition_index);

		for (uint32_t i = 0; i < size_of_partition; i++)
		{
			m_hardware.pStrip->set_pixel_color(current_position + i, current_color.red, current_color.green, current_color.blue);
			m_hardware.pStrip->set_pixel_color(total_leds - current_position - i, current_color.red, current_color.green, current_color.blue);
		}

		m_hardware.pStrip->commit();

		// Control aspect starts here
		int pressed_button = m_hardware.pButtons->checkButtons();
		if (pressed_button == main_buttons.slower_button && pulse_delay<200)
		{
			pulse_delay += 5;
			show_current_delay(pulse_delay);
		}

		if (pressed_button == main_buttons.faster_button && pulse_delay > 0)
		{
			pulse_delay -= 5;
			show_current_delay(pulse_delay);
		}

		if (pressed_button == main_buttons.smaller_partition || pressed_button == main_buttons.larger_partition)
		{
			if (pressed_button == main_buttons.smaller_partition && number_of_partitions > 3)
			{
				number_of_partitions--;
				show_current_partitions(number_of_partitions);
			}

			if (pressed_button == main_buttons.larger_partition && number_of_partitions < 10)
			{
				number_of_partitions++;
				show_current_partitions(number_of_partitions);
			}

			size_of_partition = total_leds / number_of_partitions;
			current_partition_index = 0;
		}

		if (pressed_button == main_buttons.back_button)
		{
			back_pressed = true;
		}

		if (pressed_button == main_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(current_color, pulse_delay, number_of_partitions);

			initialise_main_interface(main_buttons);
			show_current_delay(pulse_delay);
		}

		// Control aspect ends here

		delay(pulse_delay);
	}
}

ChaseEffectSetup::ChaseEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, ChaseEffect *effect) : EffectSetupBase(hardware, state_machine)
{
	m_effect = effect;
}

String ChaseEffectSetup::name()
{
	return "Chase";
}

void ChaseEffectSetup::engage()
{
	initialise_screen_base(String ("Chase mode"));
	setup_loop();
}