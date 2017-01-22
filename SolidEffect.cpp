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

void SolidEffect::setup(LEDRGB &color)
{
	m_current_color = color;
}

void SolidEffect::preview()
{
	m_state_machine->set_state(Previewing);
}

void SolidEffect::start_painting()
{
	m_painting = true;
	m_state_machine->reset();
	m_strip->set_total_strip_colour(m_current_color);
}

void SolidEffect::loop()
{
	if (m_painting == false)
	{
		return;
	}

	PaintingState painting_state = m_state_machine->get_state();

	switch (painting_state)
	{
	case StoppedPainting:
	{
		m_strip->clear_strip();
		break;
	}
	case Exit:
	{
		m_painting = false;
		break;
	}
	default:
		break;
	}
}

SolidEffect::SolidEffect(PaintingStateMachine *state_machine, LEDStick *pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}