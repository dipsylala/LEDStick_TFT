#include "BitmapEffectSetup.h"

void BitmapEffectSetup::initialise_sd_read_menu(SdCardCancelButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	buttons.back_button = add_back_button();
	m_hardware.pButtons->drawButtons();
}

void BitmapEffectSetup::initialise_main_interface(BitmapSelectionButtons &buttons)
{
	m_hardware.pButtons->deleteAllButtons();
	buttons.slower_frame = m_hardware.pButtons->addButton(220, 20, 40, 40, "-");
	buttons.faster_frame = m_hardware.pButtons->addButton(270, 20, 40, 40, "+");

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print("Repeat", 10, 90);
	buttons.repeat_paint_toggle = m_hardware.pButtons->addButton(110, 80, 40, 40, "", BUTTON_SYMBOL);
	m_hardware.pTft->print("Offset", 10, 130);
	buttons.random_offset_toggle = m_hardware.pButtons->addButton(110, 120, 40, 40, "", BUTTON_SYMBOL);

	buttons.previous_bitmap = m_hardware.pButtons->addButton(225, 180, 40, 40, "a", BUTTON_SYMBOL);
	buttons.next_bitmap = m_hardware.pButtons->addButton(270, 180, 40, 40, "b", BUTTON_SYMBOL);

	buttons.back_button = add_back_button();
	buttons.go_button = add_go_button();
	m_hardware.pButtons->drawButtons();
}

bool BitmapEffectSetup::setup_sdcard()
{
	SdCardCancelButtons sd_initialise_buttons;

	m_hardware.pTft->setColor(255, 255, 255);

	initialise_sd_read_menu(sd_initialise_buttons);

	bool card_valid = false;

	File  sd_root_directory = SD.open("/");
	sd_root_directory.rewindDirectory();

	if (sd_root_directory)
	{
		// card already initialised from previous use.
		card_valid = true;
	}

	sd_root_directory.close();

	while (card_valid == false)
	{
		if (m_hardware.pTouch->dataAvailable() == true)
		{
			if (m_hardware.pButtons->checkButtons() == sd_initialise_buttons.back_button)
			{
				return false;
			}
		}

		m_hardware.pTft->setFont(arial_bold);

		if (SD.begin(SD_PIN))
		{
			card_valid = true;
			continue;
		}
		
		m_hardware.pTft->print("Insert SD Card", CENTER, 100);
		delay(1000);
		m_hardware.pTft->print("              ", CENTER, 100);
		delay(500);
	}

	m_hardware.pTft->setFont(arial_bold);
	m_hardware.pTft->print("Card Inserted", CENTER, 100);

	delay(1000);
	return true;
}

void BitmapEffectSetup::clear_stored_files(bool free_allocated_bitmaps)
{
	for (int i = 0; i < 255; i++)
	{
		if (free_allocated_bitmaps && m_bitmap_filenames[i] != NULL)
		{
			delete m_bitmap_filenames[i];
		}

		m_bitmap_filenames[i] = NULL;
	}
}

void BitmapEffectSetup::read_filenames_from_sdcard()
{
	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print("Scanning Files", CENTER, 30);

	File sd_root_directory = SD.open("/");
	sd_root_directory.rewindDirectory();
	
	m_num_bitmaps = get_sdcard_filenames(sd_root_directory, 0);

	sd_root_directory.close();

	m_hardware.pTft->setFont(arial_bold);

	m_hardware.pTft->print(String(m_num_bitmaps) + " Found", CENTER, 70);
	
	m_hardware.pTft->print("Now the fun begins", CENTER, 90);
	delay(2000);
}

int BitmapEffectSetup::get_sdcard_filenames(File directory, int file_count)
{
	m_hardware.pTft->setFont(SmallFont);
	m_hardware.pTft->setColor(255, 255, 255);

	while (true)
	{
		File entry = directory.openNextFile();

		if (!entry)
		{
			m_hardware.pTft->print("               ", 20, 50);
			return file_count;
		}

		// Not going to recurse - we'll look only in the root directory
		if (entry.isDirectory() == false)
		{
			String current_filename = entry.name();
			m_hardware.pTft->setColor(255, 255, 255);
			m_hardware.pTft->print(current_filename + "   ", 20, 50);

			if (current_filename.endsWith(".bmp")
				|| current_filename.endsWith(".BMP")) // find files with our extension only
			{
				m_bitmap_filenames[file_count] = new String(entry.name());
				file_count++;
			}
		}

		entry.close();
	}
}

void BitmapEffectSetup::display_repeat(BitmapSelectionButtons &buttons, boolean repeat)
{
	m_hardware.pButtons->relabelButton(buttons.repeat_paint_toggle, repeat == true?(char*)"T\0":(char*)(" \0"), true);
}

void BitmapEffectSetup::display_random_offset(BitmapSelectionButtons &buttons, boolean random_offset)
{
	m_hardware.pButtons->relabelButton(buttons.random_offset_toggle, random_offset == true ? (char*)"T\0" : (char*)(" \0"), true);
}

void BitmapEffectSetup::display_frame_delay(uint32_t frame_delay)
{
	m_hardware.pTft->setFont(SmallFont);
	m_hardware.pTft->setBackColor(0, 0, 0);
	m_hardware.pTft->setColor(255, 255, 255);

	// 0-200 scale but we jump in steps of 5
	// Also, we want slower to have a low percentage, and faster to have a higher percentage
	uint8_t percentage = 100-((frame_delay) / 2);

	m_hardware.pTft->print(String(percentage) + "% ", 170, 30);
}

void BitmapEffectSetup::calculate_time_to_display(uint32_t frame_delay, Bitmap bitmap)
{
	uint32_t max_distance = bitmap.bitmap_info.imgHeight > bitmap.bitmap_info.imgWidth ? bitmap.bitmap_info.imgHeight : bitmap.bitmap_info.imgWidth;

	float total_time = ((bitmap.bitmap_info.imgHeight * frameDelay) * 6) / (float)1000;

	m_hardware.pTft->print(String(total_time) + " Secs  ", 170, 70);
}

void BitmapEffectSetup::display_current_bitmap(uint32_t x, uint32_t y, uint32_t display_width, uint32_t display_height)
{
	char szFilename[14];
	m_current_bitmap.filename.toCharArray(szFilename, 14);

	File bitmap_file = SD.open(szFilename);

	clear_space(x, y, x + display_width, y + display_height);

	float ratio_height = (float)m_current_bitmap.bitmap_info.imgHeight / (float)display_height;
	float ratio_width = (float)m_current_bitmap.bitmap_info.imgWidth / (float)display_width;
	float total_display_ratio = ratio_height > ratio_width ? ratio_height : ratio_width;

	RGB *line = new RGB[m_current_bitmap.bitmap_info.imgWidth];

	for (int display_line = 0; display_line < display_height; display_line++)
	{
		if (display_line * total_display_ratio >= m_current_bitmap.bitmap_info.imgHeight)
		{
			break;
		}

		m_current_bitmap.read_image_line(bitmap_file, m_current_bitmap.bitmap_info.imgHeight - 1 - (display_line * total_display_ratio), line, m_current_bitmap.bitmap_info.imgWidth);

		for (int display_x = 0; display_x < display_width; display_x++)
		{
			uint32_t pixel = ratio_width * display_x;

			if (pixel > m_current_bitmap.bitmap_info.imgWidth)
			{
				break;
			}

			m_hardware.pTft->setColor(line[pixel].red, line[pixel].green, line[pixel].blue);
			m_hardware.pTft->drawPixel(x + display_x, y + display_line);
		}
	}

	delete line;
}

void BitmapEffectSetup::retrieve_bitmap_details(String bitmap_filename)
{
	m_hardware.pTft->setFont(SmallFont);

	clear_space(10, 30, 150, 30 + m_hardware.pTft->getFontYsize());

	m_hardware.pTft->setColor(255, 255, 255);
	m_hardware.pTft->print(bitmap_filename, 10, 30);
	
	char szFilename[14];
	bitmap_filename.toCharArray(szFilename, 14);
	File bitmap_file = SD.open(szFilename, FILE_READ);
	int32_t info_result = m_current_bitmap.read_bitmap_info(bitmap_file);
	bitmap_file.close();

	clear_space(10, 50, 100, 50 + m_hardware.pTft->getFontYsize());

	if (info_result == BMP_INVALID_FILE)
	{
		m_hardware.pTft->print("Not a bitmap", 10, 100);
	}
	else if (info_result == BMP_INVALID_BMP_FORMAT)
	{ 
		m_hardware.pTft->print("Not a supported bitmap format", 10, 100);
	}
	else 
	{
		m_hardware.pTft->setColor(255, 255, 255);
		m_hardware.pTft->print(String(m_current_bitmap.bitmap_info.imgWidth) + " X " + String(m_current_bitmap.bitmap_info.imgHeight) + "  ", 10, 50);
	}
}


void BitmapEffectSetup::setup_loop()
{
	boolean default_colors = true;
	int pressed_button;
	boolean exit_pressed = false;
	boolean repeat_bitmap = false;
	boolean random_offset = false;

	uint32_t frame_delay = 30;

	BitmapSelectionButtons bitmap_selection_buttons;
	initialise_main_interface(bitmap_selection_buttons);
	
	display_frame_delay(frame_delay);
	retrieve_bitmap_details(*(m_bitmap_filenames[m_current_file_index]));
	calculate_time_to_display(frameDelay, m_current_bitmap);
	display_repeat(bitmap_selection_buttons, repeat_bitmap);
	display_random_offset(bitmap_selection_buttons, random_offset);
	display_current_bitmap(110, 30, 40, 40);


	while (exit_pressed == false)
	{
		if (m_hardware.pTouch->dataAvailable() == false)
		{
			continue;
		}

		pressed_button = m_hardware.pButtons->checkButtons();

		if (pressed_button == bitmap_selection_buttons.previous_bitmap || pressed_button == bitmap_selection_buttons.next_bitmap)
		{
			if (pressed_button == bitmap_selection_buttons.previous_bitmap)
			{
				if (m_current_file_index > 0)
				{
					m_current_file_index--;
				}
				else
				{
					m_current_file_index = m_num_bitmaps - 1;
				}
			}

			if (pressed_button == bitmap_selection_buttons.next_bitmap)
			{
				if (m_current_file_index < m_num_bitmaps - 1)
				{
					m_current_file_index++;
				}
				else
				{
					m_current_file_index = 0;
				}
			}

			retrieve_bitmap_details(*(m_bitmap_filenames[m_current_file_index]));
			calculate_time_to_display(frameDelay, m_current_bitmap);
			display_current_bitmap(110, 30, 40, 40);
		}

		if (pressed_button == bitmap_selection_buttons.slower_frame || pressed_button == bitmap_selection_buttons.faster_frame)
		{
			if (pressed_button == bitmap_selection_buttons.faster_frame && frame_delay >= 5)
			{
				frame_delay -= 5;
			}

			if (pressed_button == bitmap_selection_buttons.slower_frame && frame_delay <= 195)
			{
				frame_delay += 5;
			}

			display_frame_delay(frame_delay);
			calculate_time_to_display(frame_delay, m_current_bitmap);
		}
		
		if (pressed_button == bitmap_selection_buttons.repeat_paint_toggle)
		{
			repeat_bitmap = !repeat_bitmap;
			display_repeat(bitmap_selection_buttons, repeat_bitmap);
		}

		if (pressed_button == bitmap_selection_buttons.random_offset_toggle)
		{
			random_offset = !random_offset;
			display_random_offset(bitmap_selection_buttons, random_offset);
		}

		if (pressed_button == bitmap_selection_buttons.go_button)
		{
			prepare_screen_for_effect();
			m_effect->start_painting(m_current_bitmap, frame_delay, repeat_bitmap, random_offset);
			
			initialise_screen_base(String("Bitmap mode"));
			initialise_main_interface(bitmap_selection_buttons);
			retrieve_bitmap_details(*(m_bitmap_filenames[m_current_file_index]));
			calculate_time_to_display(frameDelay, m_current_bitmap);
			display_frame_delay(frame_delay);
			calculate_time_to_display(frame_delay, m_current_bitmap);
			display_repeat(bitmap_selection_buttons, repeat_bitmap);
			display_random_offset(bitmap_selection_buttons, random_offset);
			display_current_bitmap(110, 30, 40, 40);
		}

		if (pressed_button == bitmap_selection_buttons.back_button)
		{
			exit_pressed = true;
		}
	}
}


BitmapEffectSetup::BitmapEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, BitmapEffect *effect) : BaseEffectSetup(hardware, state_machine)
{
	m_effect = effect;
}

void BitmapEffectSetup::set_blank_bitmap_page()
{
	initialise_screen_base(String("Bitmap mode"));
}

String BitmapEffectSetup::name()
{
	return "Bitmap";
}

void BitmapEffectSetup::engage()
{
	set_blank_bitmap_page();
	
	bool sd_card_setup = setup_sdcard();

	m_hardware.pButtons->deleteAllButtons();

	if (sd_card_setup == false)
	{
		return;
	}
	
	clear_stored_files(false);

	set_blank_bitmap_page();
	read_filenames_from_sdcard();

	set_blank_bitmap_page();

	setup_loop();

	clear_stored_files(true);
}