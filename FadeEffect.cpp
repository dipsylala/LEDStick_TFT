#include "FadeEffect.h"

void FadeEffect::start_painting(FadeConfiguration &fade_configuration, int pulse_delay)
{
	m_state_machine->reset();

	boolean exit_pressed = false;
	int colour_index = 0;
	int next_colour_index = 1;
	uint32_t steps_between_colours = 30;
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
