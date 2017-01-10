#include "PaintingStateMachine.h"


void PaintingStateMachine::reset() 
{
	current_state = Waiting;
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