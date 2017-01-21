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

#include "SolidEffect.h"

void SolidEffect::start_painting(LEDRGB &color)
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