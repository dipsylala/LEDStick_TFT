// LEDStick.h

#ifndef _LEDSTICK_h
#define _LEDSTICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include "RGB.h"

#define GPIO_PIN 8 

class LEDStick
{
private:
	Adafruit_NeoPixel *m_neoPixel;
	uint32_t m_num_pixels;

public:
	void set_total_strip_colour(RGB colour);
	void set_total_strip_colour(uint32_t red, uint32_t green, uint32_t blue);
	void set_rgb_strip_color(RGB* colours, uint16_t num_rgb);

	void commit();
	void clear_strip();
	void set_pixel_color(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
	void set_stick_length(uint16_t length);
	uint16_t get_stick_length();
	LEDStick(uint32_t num_pixels);

};

#endif

