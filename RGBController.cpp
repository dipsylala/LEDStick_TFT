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