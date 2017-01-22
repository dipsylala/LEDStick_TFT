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

#include "PaintingStateMachine.h"


void PaintingStateMachine::reset() 
{
	current_state = Dormant;
}

PaintingState PaintingStateMachine::get_state()
{
	if (read_state_jump() == false)
	{
		return current_state;
	}

	int state = (int)current_state;
	state++;
	current_state = (PaintingState)state;

	return current_state;
}

void PaintingStateMachine::set_state(PaintingState state)
{
	current_state = state;
}

bool PaintingStateMachine::read_state_jump()
{
	if (m_hardware.pTouch->dataAvailable() == false && digitalRead(EFFECT_TRIGGER) == LOW)
	{
		return false;
	}

	if (m_hardware.pTouch->dataAvailable() == true)
	{
		while (m_hardware.pTouch->dataAvailable() == true)
		{
		}

		delay(50);
		return true;
	}

	int unfiltered_pin_state = digitalRead(EFFECT_TRIGGER);

	if (unfiltered_pin_state != last_button_state) 
	{
		// reset the debouncing timer
		last_debounce_time = millis();
	}

	if ((millis() - last_debounce_time) > debounce_delay
		&& unfiltered_pin_state != current_pin_state)
	{
		current_pin_state = unfiltered_pin_state;

		if (current_pin_state == HIGH)
		{
			return true;
		}
	}

	return false;
}

PaintingStateMachine::PaintingStateMachine(StickHardware hardware)
{
	m_hardware = hardware;

	pinMode(EFFECT_TRIGGER, INPUT);
}