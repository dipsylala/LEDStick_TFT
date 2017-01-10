#include "SolidEffectSetup.h"


void SolidEffectSetup::initialise_main_interface(SolidSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	buttons.back_button = add_back_button();
	buttons.go_button = buttons.go_button = add_go_button();

	rgbController.create_interface_components(m_hardware, 40, 20);

	m_hardware.pButtons->drawButtons();
}

// Configuring the effect - may or may not include a 'preview' on the stick itself
void SolidEffectSetup::setup_loop()
{
	SolidSelectionButtons main_buttons;
	initialise_main_interface(main_buttons);

	boolean back_pressed = false;
	RGB current_color = create_rgb(128, 128, 128);
	boolean has_changed = true;
	boolean led_on = true;

	while (back_pressed == false)
	{
		if (has_changed)
		{
			m_hardware.pStrip->set_total_strip_colour(current_color);
		}

		if (!m_hardware.pTouch->dataAvailable())
		{
			continue;
		}

		m_hardware.pTouch->read();

		int16_t x = m_hardware.pTouch->getX();
		int16_t y = m_hardware.pTouch->getY();

		int pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == main_buttons.back_button)
		{
			back_pressed = true;
		}

		if (pressed_button == main_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(current_color);
			initialise_main_interface(main_buttons);
		}

		rgbController.check_point(x, y, current_color, has_changed);
	}
}

SolidEffectSetup::SolidEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, SolidEffect *effect) : BaseEffectSetup(hardware, state_machine)
{
	m_effect = effect;
}

String SolidEffectSetup::name()
{
	return "Solid";
}

void SolidEffectSetup::engage()
{
	initialise_screen_base(String ("Solid mode"));
	setup_loop();
}