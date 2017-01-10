#include "StarEffect.h"

void StarEffect::start_painting(int gap_time, int star_time)
{
	m_state_machine->reset();

	boolean exit_pressed = false;
	int num_pixels = m_strip->get_stick_length();

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
			int random_pixel = random(num_pixels);

			m_strip->set_pixel_color(random_pixel, 255, 255, 255);
			m_strip->commit();
			m_strip->clear_strip();

			delay(star_time);

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

		delay(gap_time);
	}
}

StarEffect::StarEffect(PaintingStateMachine * state_machine, LEDStick * pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}