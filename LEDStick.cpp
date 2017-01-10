#include "LEDStick.h"

void LEDStick::clear_strip()
{
	for (uint16_t i = 0; i < m_num_pixels; i++)
	{
		m_neoPixel->setPixelColor(i, 0, 0, 0);
	}

	m_neoPixel->show();
}

void LEDStick::set_rgb_strip_color(RGB* colours, uint16_t num_rgb)
{
	for (uint16_t i = 0; i < num_rgb; i++)
	{
		m_neoPixel->setPixelColor(i, colours[i].red, colours[i].green, colours[i].blue);
	}

	m_neoPixel->show();
}

void LEDStick::set_total_strip_colour(RGB colour)
{
	set_total_strip_colour(colour.red, colour.green, colour.blue);
}

void LEDStick::commit()
{
	m_neoPixel->show();
}

void LEDStick::set_total_strip_colour(uint8_t red, uint8_t green, uint8_t blue)
{
	for (uint16_t i = 0; i < m_num_pixels; i++)
	{
		m_neoPixel->setPixelColor(i, red, green, blue);
	}

	m_neoPixel->show();
}

void LEDStick::set_pixel_color(uint16_t pixel_index, uint8_t red, uint8_t green, uint8_t blue)
{
	m_neoPixel->setPixelColor(pixel_index, red, green, blue);
}

void LEDStick::set_stick_length(uint16_t length)
{
	m_neoPixel->updateLength(length);
}

uint16_t LEDStick::get_stick_length()
{
	return m_num_pixels;
}

LEDStick::LEDStick(uint16_t num_pixels)
{
	m_num_pixels = num_pixels;
	m_neoPixel = new Adafruit_NeoPixel(num_pixels, GPIO_PIN, NEO_GRB + NEO_KHZ800);
	m_neoPixel->begin();
	m_neoPixel->show();
}