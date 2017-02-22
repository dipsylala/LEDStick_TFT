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

#include "ChaseEffect.h"

void ChaseEffect::start_painting(RGB &color, uint32_t pulse_delay, uint32_t number_of_partitions)
{
	uint32_t total_leds = m_strip->get_stick_length();
	uint32_t current_partition_index = 0;
	uint32_t size_of_partition = total_leds / number_of_partitions;

	m_state_machine->reset();

	boolean exit_pressed = false;

	m_strip->clear_strip();

	while (exit_pressed == false)
	{
		PaintingState painting_state = m_state_machine->get_state();

		switch (painting_state)
		{
		case StoppedPainting:
		{
			m_strip->clear_strip();
			break;
		}
		case Painting:
		{
			if (current_partition_index == number_of_partitions - 2)
			{
				current_partition_index = 0;
			}
			else
			{
				current_partition_index++;
			}

			m_strip->clear_strip(false);

			uint32_t current_position = (size_of_partition * current_partition_index);

			for (uint32_t i = 0; i < size_of_partition; i++)
			{
				if (current_position + i > total_leds)
				{
					break;
				}

				m_strip->set_pixel_color(current_position + i, color.red, color.green, color.blue);
				m_strip->set_pixel_color(total_leds - current_position - i, color.red, color.green, color.blue);
			}

			m_strip->commit();
			delay(pulse_delay);
			break;
		}
		case Exit:
		{
			exit_pressed = true;
			break;
		}
		default:
			break;
		}
	}

	m_strip->clear_strip();
}

ChaseEffect::ChaseEffect(PaintingStateMachine *state_machine, LEDStick *pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}