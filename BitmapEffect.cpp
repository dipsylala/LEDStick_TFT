#include "BitmapEffect.h"

void BitmapEffect::start_painting(Bitmap &bitmap, uint32_t frame_delay, bool repeat, bool random_offset)
{
	m_state_machine->reset();

	boolean exit_pressed = false;

	char szFilename[14];
	bitmap.filename.toCharArray(szFilename, 14);

	File bitmap_file = SD.open(szFilename);

	Bitmap bitmap_to_display;
	bitmap_to_display.read_bitmap_info(bitmap_file);

	uint16_t bitmap_width = bitmap_to_display.bitmap_info.imgWidth;
	
	uint16_t num_pixels = m_strip->get_stick_length();

	RGB *rgb_line = new RGB[num_pixels];

	uint32_t bitmap_line = 0;
	uint32_t offset = 0;
	if (random_offset == true)
	{
		offset = get_random_position(num_pixels, bitmap_to_display);
	}

	unsigned long start = millis();

	while (exit_pressed == false)
	{
		PaintingState painting_state = m_state_machine->get_state();

		switch (painting_state)
		{
		case StoppedPainting:
		{
			m_strip->clear_strip();
			break;
		}
		case Painting:
		{
			memset(rgb_line, 0, num_pixels * sizeof (RGB));
			bitmap.read_image_line(bitmap_file, bitmap_line, rgb_line + offset, bitmap_width);

			m_strip->set_rgb_strip_color(rgb_line, num_pixels);

			bitmap_line++;

			if (bitmap_line == bitmap.bitmap_info.imgHeight)
			{
				if (repeat == true)
				{
					if (random_offset == true)
					{
						offset = get_random_position(m_strip->get_stick_length(), bitmap_to_display);
					}
					
					bitmap_line = 0;
				}
				else
				{
					unsigned long stop = millis();
					Serial.println("Duration: " + String(stop - start));
					m_state_machine->set_state(StoppedPainting);
				}
			}
			delay(frame_delay);
			break;
		}
		case Exit:
		{
			exit_pressed = true;
			break;
		}
		default:
			break;
		}
	}

	delete rgb_line;
	bitmap_file.close();
}


uint16_t BitmapEffect::get_random_position(uint16_t num_pixels, Bitmap bitmap)
{
	return random(0, num_pixels - bitmap.bitmap_info.imgWidth);
}

BitmapEffect::BitmapEffect(PaintingStateMachine * state_machine, LEDStick * pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}