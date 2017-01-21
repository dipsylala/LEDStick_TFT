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

#ifndef _LEDSTICK_h
#define _LEDSTICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <fastled.h>
#include <colorutils.h>
#include "LEDRGB.h"

#define GPIO_PIN 8 
#define MAX_LEDS 512

class LEDStick
{
private:
	CRGB m_leds[MAX_LEDS];
	uint16_t m_num_pixels;

public:
	void set_total_strip_colour(LEDRGB colour);
	void set_total_strip_colour(uint8_t red, uint8_t green, uint8_t blue);
	void set_rgb_strip_color(LEDRGB* colours, uint16_t num_rgb);

	void commit();
	void clear_strip();
	void set_pixel_color(uint16_t pixel_index, uint8_t red, uint8_t green, uint8_t blue);
	void set_stick_length(uint16_t length);
	uint16_t get_stick_length();
	LEDStick(uint16_t num_pixels);
};

#endif

