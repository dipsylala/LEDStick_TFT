#include "LEDStick.h"

void LEDStick::clear_strip()
{
	for (int i = 0; i < m_num_pixels; i++)
	{
		m_neoPixel->setPixelColor(i, 0, 0, 0);
	}

	m_neoPixel->show();
}

void LEDStick::set_rgb_strip_color(RGB* colours, uint16_t num_rgb)
{
	uint16_t actual_number = num_rgb < m_num_pixels ? num_rgb : m_num_pixels;

	for (uint16_t i = 0; i < actual_number; i++)
	{
		m_neoPixel->setPixelColor(i, colours[i].red, colours[i].green, colours[i].blue);
	}

	for (uint16_t i = actual_number; i < m_num_pixels; i++)
	{
		m_neoPixel->setPixelColor(i, 0, 0, 0);
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

void LEDStick::set_total_strip_colour(uint32_t red, uint32_t green, uint32_t blue)
{
	for (int i = 0; i < m_num_pixels; i++)
	{
		m_neoPixel->setPixelColor(i, red, green, blue);
	}

	m_neoPixel->show();
}

void LEDStick::set_pixel_color(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
	m_neoPixel->setPixelColor(n, r, g, b);
}

void LEDStick::set_stick_length(uint16_t length)
{
	m_neoPixel->updateLength(length);
}

uint16_t LEDStick::get_stick_length()
{
	return m_num_pixels;
}

LEDStick::LEDStick(uint32_t num_pixels)
{
	m_num_pixels = num_pixels;
	m_neoPixel = new Adafruit_NeoPixel(num_pixels, GPIO_PIN, NEO_GRB + NEO_KHZ800);
	m_neoPixel->begin();
	m_neoPixel->show();
}