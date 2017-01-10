#include "BaseEffectSetup.h"

void BaseEffectSetup::initialise_screen_base(String title)
{
	m_hardware.pTft->clrScr();
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->setColor(255, 0, 255);
	m_hardware.pTft->print(title, CENTER, 0);
}

void BaseEffectSetup::clear_space(int x1, int y1, int x2, int y2)
{
	m_hardware.pTft->setBackColor(0, 0, 0);
	m_hardware.pTft->setColor(0, 0, 0);
	m_hardware.pTft->fillRect(x1, y1, x2, y2);
}

RGB BaseEffectSetup::create_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	RGB colour;
	colour.red = red;
	colour.green = green;
	colour.blue = blue;
	return colour;
}

int BaseEffectSetup::add_back_button()
{
	return m_hardware.pButtons->addButton(10, 180, 100, 40, "Back");
}

int BaseEffectSetup::add_go_button()
{
	return m_hardware.pButtons->addButton(115, 180, 100, 40, "Go");
}

void BaseEffectSetup::prepare_screen_for_effect()
{
	m_hardware.pButtons->deleteAllButtons();
	m_hardware.pTft->clrScr();
}

BaseEffectSetup::BaseEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine)
{
	m_hardware = hardware;
	m_state_machine = state_machine;
}
