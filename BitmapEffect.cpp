#include "BitmapEffect.h"

void BitmapEffect::start_painting(Bitmap &bitmap, uint32_t frame_delay, bool repeat)
{
	m_state_machine->reset();

	boolean exit_pressed = false;

	char szFilename[14];
	bitmap.filename.toCharArray(szFilename, 14);

	File bitmap_file = SD.open(szFilename);

	Bitmap bitmap_to_display;
	bitmap_to_display.read_bitmap_info(bitmap_file);

	uint16_t bitmap_width = bitmap_to_display.bitmap_info.imgWidth;
	RGB *rgb_line = new RGB[bitmap_width];

	uint32_t bitmap_line = 0;

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
			bitmap.read_image_line(bitmap_file, bitmap_line, rgb_line, bitmap_width);

			m_strip->set_rgb_strip_color(rgb_line, bitmap_width);

			bitmap_line++;

			if (bitmap_line == bitmap.bitmap_info.imgHeight)
			{
				if (repeat == true)
				{
					bitmap_line = 0;
				}
				else
				{
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


BitmapEffect::BitmapEffect(PaintingStateMachine * state_machine, LEDStick * pStrip)
{
	m_state_machine = state_machine;
	m_strip = pStrip;
}