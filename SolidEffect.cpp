#include "SolidEffect.h"

void SolidEffect::start_painting(RGB &color)
{
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
			m_strip->set_total_strip_colour(color);
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

SolidEffect::SolidEffect(PaintingStateMachine *state_machine, LEDStick *pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}