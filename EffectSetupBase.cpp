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

#include "EffectSetupBase.h"

void EffectSetupBase::initialise_screen_base(String title)
{
	m_hardware.pTft->clrScr();
	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->setColor(255, 0, 255);
	m_hardware.pTft->print(title, CENTER, 0);
}

void EffectSetupBase::clear_space(int x1, int y1, int x2, int y2)
{
	m_hardware.pTft->setBackColor(0, 0, 0);
	m_hardware.pTft->setColor(0, 0, 0);
	m_hardware.pTft->fillRect(x1, y1, x2, y2);
}

RGB EffectSetupBase::create_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	RGB colour;
	colour.red = red;
	colour.green = green;
	colour.blue = blue;
	return colour;
}

int EffectSetupBase::add_back_button()
{
	return m_hardware.pButtons->addButton(10, 180, 100, 40, "Back");
}

int EffectSetupBase::add_go_button()
{
	return m_hardware.pButtons->addButton(115, 180, 100, 40, "Go");
}

void EffectSetupBase::prepare_screen_for_effect()
{
	m_hardware.pButtons->deleteAllButtons();
	m_hardware.pTft->clrScr();
}

EffectSetupBase::EffectSetupBase(StickHardware hardware, PaintingStateMachine *state_machine)
{
	m_hardware = hardware;
	m_state_machine = state_machine;
}
