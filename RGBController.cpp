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

#include "RGBController.h"
#include "RGBBitmap.h"

#define RGB_SCALE 10

void RGBController::create_interface_components(StickHardware hardware, uint32_t x, uint32_t y)
{
	m_hardware = hardware;

	m_xmin = x;
	m_xmax = (COLOR_PICKER_WIDTH * RGB_SCALE) + x;

	m_ymin = y;
	m_ymax = (COLOR_PICKER_HEIGHT * RGB_SCALE) + y;
	
	hardware.pTft->drawBitmap(x, y, COLOR_PICKER_WIDTH, COLOR_PICKER_HEIGHT, (unsigned int*)color_picker_bmp, RGB_SCALE);
}

void RGBController::check_point(uint32_t x, uint32_t y, RGB &rgb, boolean has_changed)
{
	if (x < m_xmin || y < m_ymin || x > m_xmax || y > m_ymax)
	{
		has_changed = false;
		return;
	}

	m_hardware.pTft->setColor(255, 0, 0);
	uint32_t point_in_bitmap_x = (x - m_xmin) / RGB_SCALE;
	uint32_t point_in_bitmap_y = (y - m_ymin) / RGB_SCALE;

	uint32_t color = pgm_read_word(color_picker_bmp + (point_in_bitmap_y * COLOR_PICKER_WIDTH) + point_in_bitmap_x);
	
	rgb.red = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
	rgb.green = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
	rgb.blue = (((color & 0x1F) * 527) + 23) >> 6;

	has_changed = true;
}