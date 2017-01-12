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

#include "FadeEffect.h"

void FadeEffect::start_painting(FadeConfiguration &fade_configuration, uint32_t pulse_delay, uint32_t steps_between_colours)
{
	m_state_machine->reset();

	boolean exit_pressed = false;
	int colour_index = 0;
	int next_colour_index = 1;
	uint32_t current_colour_step = 0;

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
			RGB current_colours = calculate_current_colour(fade_configuration.colour_spread[colour_index],
				fade_configuration.colour_spread[next_colour_index],
				current_colour_step,
				steps_between_colours);

			m_strip->set_total_strip_colour(current_colours.red, current_colours.green, current_colours.blue);

			if (current_colour_step == steps_between_colours)
			{
				current_colour_step = 0;
				colour_index = next_colour_index;
				next_colour_index = (colour_index < fade_configuration.num_colours - 1) ? colour_index + 1 : 0;
			}
			else
			{
				current_colour_step++;
			}

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

FadeEffect::FadeEffect(PaintingStateMachine * state_machine, LEDStick * pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}
