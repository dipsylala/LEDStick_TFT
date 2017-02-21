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

	buttons.previous_config = m_hardware.pButtons->addButton(220, 120, 40, 40, "a", BUTTON_SYMBOL);
	buttons.next_config = m_hardware.pButtons->addButton(270, 120, 40, 40, "b", BUTTON_SYMBOL);

	buttons.go_button = add_go_button();

	buttons.back_button = add_back_button();

	m_hardware.pButtons->drawButtons();
}

void ChaseEffectSetup::show_selected_configuration(ChaseConfiguration &chase_configuration)
{
	char nameBuf[20];
	chase_configuration.name.toCharArray(nameBuf, 20);

	m_hardware.pTft->setFont(arial_bold);
	clear_space(20, 130, 219, 130 + m_hardware.pTft->getFontYsize());

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print(chase_configuration.name, 20, 130);
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
	m_hardware.pTft->print("Steps: " + String(partition_size) + " ", 20, 80);
}

int ChaseEffectSetup::read_chases_from_source(ChaseConfiguration **chase_configuration)
{
	int num_configurations = 15;

	*chase_configuration = new ChaseConfiguration[num_configurations];

	(*chase_configuration)[0].name = "White";
	(*chase_configuration)[0].colour = create_rgb(0xFFFFFF);
	(*chase_configuration)[1].name = "Silver";
	(*chase_configuration)[1].colour = create_rgb(0xC0C0C0);
	(*chase_configuration)[2].name = "Gray"; 
	(*chase_configuration)[2].colour = create_rgb(0x808080);
	(*chase_configuration)[3].name = "Red";
	(*chase_configuration)[3].colour = create_rgb(0xFF0000);
	(*chase_configuration)[4].name = "Maroon";
	(*chase_configuration)[4].colour = create_rgb(0x800000);
	(*chase_configuration)[5].name = "Yellow";
	(*chase_configuration)[5].colour = create_rgb(0xFFFF00);
	(*chase_configuration)[6].name = "Olive";
	(*chase_configuration)[6].colour = create_rgb(0x808000);
	(*chase_configuration)[7].name = "Lime"; 
	(*chase_configuration)[7].colour = create_rgb(0x00FF00);
	(*chase_configuration)[8].name = "Green";
	(*chase_configuration)[8].colour = create_rgb(0x008000);
	(*chase_configuration)[9].name = "Aqua"; 
	(*chase_configuration)[9].colour = create_rgb(0x00FFFF);
	(*chase_configuration)[10].name = "Teal"; 
	(*chase_configuration)[10].colour = create_rgb(0x008080);
	(*chase_configuration)[11].name = "Blue";
	(*chase_configuration)[11].colour = create_rgb(0x0000FF);
	(*chase_configuration)[12].name = "Navy"; 
	(*chase_configuration)[12].colour = create_rgb(0x000080);
	(*chase_configuration)[13].name = "Fuchsia";
	(*chase_configuration)[13].colour = create_rgb(0xFF00FF);
	(*chase_configuration)[14].name = "Purple";
	(*chase_configuration)[14].colour = create_rgb(0x800080);

	return num_configurations;
}

// Configuring the effect - may or may not include a 'preview' on the stick itself
void ChaseEffectSetup::setup_loop()
{
	ChaseSelectionButtons main_buttons;
	ChaseConfiguration *chase_configuration;
	int current_configuration = 0;
	int num_configurations = read_chases_from_source(&chase_configuration);
	uint32_t pulse_delay = 150;
	boolean back_pressed = false;
	uint32_t total_leds = m_hardware.pStrip->get_stick_length();

	uint32_t number_of_partitions = 7;
	uint32_t size_of_partition = total_leds / number_of_partitions;

	initialise_main_interface(main_buttons);

	uint32_t current_partition_index = 0;

	show_current_partitions(number_of_partitions);
	show_current_delay(pulse_delay);
	show_selected_configuration(chase_configuration[current_configuration]);

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
			m_hardware.pStrip->set_pixel_color(current_position + i, chase_configuration[current_configuration].colour.red, chase_configuration[current_configuration].colour.green, chase_configuration[current_configuration].colour.blue);
			m_hardware.pStrip->set_pixel_color(total_leds - current_position - i, chase_configuration[current_configuration].colour.red, chase_configuration[current_configuration].colour.green, chase_configuration[current_configuration].colour.blue);
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

			if (pressed_button == main_buttons.larger_partition && number_of_partitions < 21)
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

		if (pressed_button == main_buttons.previous_config || pressed_button == main_buttons.next_config)
		{
			if (pressed_button == main_buttons.previous_config)
			{
				if (current_configuration == 0)
				{
					current_configuration = num_configurations - 1;
				}
				else
				{
					current_configuration--;
				}
			}

			if (pressed_button == main_buttons.next_config)
			{
				if (current_configuration == num_configurations - 1)
				{
					current_configuration = 0;
				}
				else
				{
					current_configuration++;
				}
			}

			show_selected_configuration(chase_configuration[current_configuration]);
		}

		if (pressed_button == main_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(chase_configuration[current_configuration].colour, pulse_delay, number_of_partitions);

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