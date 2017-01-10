#include "FadeEffectSetup.h"

void FadeEffectSetup::initialise_main_interface(FadeSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();

	m_hardware.pButtons->setTextFont(arial_bold);
	buttons.slower_button = m_hardware.pButtons->addButton(220, 20, 40, 40, "-");
	buttons.faster_button = m_hardware.pButtons->addButton(270, 20, 40, 40, "+");

	buttons.previous_config = m_hardware.pButtons->addButton(225, 180, 40, 40, "a", BUTTON_SYMBOL);
	buttons.next_config = m_hardware.pButtons->addButton(270, 180, 40, 40, "b", BUTTON_SYMBOL);

	buttons.go_button = add_go_button();

	buttons.back_button = add_back_button();
	
	m_hardware.pButtons->drawButtons();
}

void FadeEffectSetup::set_selected_configuration(FadeConfiguration &fade_configuration)
{
	char nameBuf[50];
	fade_configuration.name.toCharArray(nameBuf, 50);

	m_hardware.pTft->setFont(arial_bold);
	clear_space(10, 85, 300, 85 + m_hardware.pTft->getFontYsize());

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print(fade_configuration.name, 10, 85);
}

void FadeEffectSetup::show_current_delay(uint32_t delay)
{
	m_hardware.pTft->setFont(arial_bold);

	clear_space(10, 30, 11 * m_hardware.pTft->getFontXsize(), 30 + m_hardware.pTft->getFontYsize());
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print("Speed: " + String(100 - delay) + "% ", 10, 30);
}

int FadeEffectSetup::read_fades_from_source(FadeConfiguration **fade_configuration)
{
	int num_configurations = 5;

	*fade_configuration = new FadeConfiguration[num_configurations];
	(*fade_configuration)[0].name = "Rainbow";
	(*fade_configuration)[0].num_colours = 7;
	(*fade_configuration)[0].colour_spread = new RGB[(*fade_configuration)[0].num_colours];
	(*fade_configuration)[0].colour_spread[0] = create_rgb(148, 0, 211);
	(*fade_configuration)[0].colour_spread[1] = create_rgb(75, 0, 130);
	(*fade_configuration)[0].colour_spread[2] = create_rgb(0, 0, 255);
	(*fade_configuration)[0].colour_spread[3] = create_rgb(0, 255, 0);
	(*fade_configuration)[0].colour_spread[4] = create_rgb(255, 255, 0);
	(*fade_configuration)[0].colour_spread[5] = create_rgb(255, 127, 0);
	(*fade_configuration)[0].colour_spread[6] = create_rgb(255, 0, 0);

	(*fade_configuration)[1].name = "Pastel";
	(*fade_configuration)[1].num_colours = 5;
	(*fade_configuration)[1].colour_spread = new RGB[(*fade_configuration)[1].num_colours];
	(*fade_configuration)[1].colour_spread[0] = create_rgb(255, 179, 186);
	(*fade_configuration)[1].colour_spread[1] = create_rgb(255, 223, 186);
	(*fade_configuration)[1].colour_spread[2] = create_rgb(255, 255, 186);
	(*fade_configuration)[1].colour_spread[3] = create_rgb(186, 255, 201);
	(*fade_configuration)[1].colour_spread[4] = create_rgb(186, 225, 255);

	(*fade_configuration)[2].name = "Red/Green";
	(*fade_configuration)[2].num_colours = 2;
	(*fade_configuration)[2].colour_spread = new RGB[(*fade_configuration)[2].num_colours];
	(*fade_configuration)[2].colour_spread[0] = create_rgb(255, 0, 0);
	(*fade_configuration)[2].colour_spread[1] = create_rgb(0, 255, 0);

	(*fade_configuration)[3].name = "Red/White/Blue";
	(*fade_configuration)[3].num_colours = 3;
	(*fade_configuration)[3].colour_spread = new RGB[(*fade_configuration)[3].num_colours];
	(*fade_configuration)[3].colour_spread[0] = create_rgb(255, 0, 0);
	(*fade_configuration)[3].colour_spread[1] = create_rgb(255, 255, 255);
	(*fade_configuration)[3].colour_spread[2] = create_rgb(0, 0, 255);

	(*fade_configuration)[4].name = "Pulsing White";
	(*fade_configuration)[4].num_colours = 2;
	(*fade_configuration)[4].colour_spread = new RGB[(*fade_configuration)[4].num_colours];
	(*fade_configuration)[4].colour_spread[0] = create_rgb(0, 0, 0);
	(*fade_configuration)[4].colour_spread[1] = create_rgb(255, 255, 255);

	return num_configurations;
}



void FadeEffectSetup::setup_loop()
{
	FadeConfiguration *fade_configuration;
	int num_configurations = read_fades_from_source(&fade_configuration);
	
	int current_configuration = 0;
	int colour_index = 0;
	int next_colour_index = 1;
	int pulse_delay = 30;
	boolean back_pressed = false;

	initialise_main_interface(m_fade_selection_buttons);

	set_selected_configuration(fade_configuration[current_configuration]);
	show_current_delay(pulse_delay);

	uint32_t steps_between_colours = 30;
	uint32_t current_colour_step = 0;
	
	while (back_pressed == false)
	{
		RGB current_colours = calculate_current_colour(fade_configuration[current_configuration].colour_spread[colour_index],
													fade_configuration[current_configuration].colour_spread[next_colour_index], 
													current_colour_step, 
													steps_between_colours);

		m_hardware.pStrip->set_total_strip_colour(current_colours.red, current_colours.green, current_colours.blue);

		if (current_colour_step == steps_between_colours)
		{
			current_colour_step = 0;
			colour_index = next_colour_index;
			next_colour_index = (colour_index < fade_configuration[current_configuration].num_colours - 1) ? colour_index + 1 : 0;
		}
		else
		{
			current_colour_step++;
		}		

		// Control aspect starts here

		int pressed_button = m_hardware.pButtons->checkButtons();
		if (pressed_button == m_fade_selection_buttons.slower_button && pulse_delay<=95)
		{
			pulse_delay += 5;
			show_current_delay(pulse_delay);
		}

		if (pressed_button == m_fade_selection_buttons.faster_button && pulse_delay >= 5)
		{
			pulse_delay -= 5;
			show_current_delay(pulse_delay);
		}

		if (pressed_button == m_fade_selection_buttons.previous_config || pressed_button == m_fade_selection_buttons.next_config)
		{
			if (pressed_button == m_fade_selection_buttons.previous_config)
			{
				if (current_configuration == 0)
				{
					current_configuration = num_configurations - 1;
				}
				else
				{
					current_configuration--;
				}
			}

			if (pressed_button == m_fade_selection_buttons.next_config)
			{
				if (current_configuration == num_configurations - 1)
				{
					current_configuration = 0;
				}
				else
				{
					current_configuration++;
				}
			}

			colour_index = 0;
			next_colour_index = 1;
			set_selected_configuration(fade_configuration[current_configuration]);
		}

		if (pressed_button == m_fade_selection_buttons.back_button)
		{
			back_pressed = true;
		}

		if (pressed_button == m_fade_selection_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(fade_configuration[current_configuration], pulse_delay);

			initialise_main_interface(m_fade_selection_buttons);
			set_selected_configuration(fade_configuration[current_configuration]);
			show_current_delay(pulse_delay);
		}

		// Control aspect ends here

		delay(pulse_delay);
	}

	for (int i = 0; i<num_configurations;i++)
	{
		delete (fade_configuration[i].colour_spread);
	}

	delete (fade_configuration);
}


FadeEffectSetup::FadeEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, FadeEffect *effect) : BaseEffectSetup(hardware, state_machine)
{
	m_effect = effect;
}

String FadeEffectSetup::name()
{
	return "Fade";
}

void FadeEffectSetup::engage()
{
	initialise_screen_base(String("Fade mode"));
	setup_loop();
}