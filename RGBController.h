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

#ifndef _RGBCONTROLLER_h
#define _RGBCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LEDRGB.h"
#include "StickHardware.h"

extern uint8_t arial_bold[];

class RGBController
{
private:

	StickHardware m_hardware;

	uint32_t m_xmin;
	uint32_t m_ymin;
	uint32_t m_xmax;
	uint32_t m_ymax;
	
public:
	void create_interface_components(StickHardware hardware, uint32_t x, uint32_t y);
	void check_point(uint32_t x, uint32_t y, LEDRGB &rgb, boolean has_changed);
};


#endif

