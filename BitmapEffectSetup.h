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

#ifndef _BITMAPEFFECTSETUP_h
#define _BITMAPEFFECTSETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>
#include <SPI.h>
#include "EffectSetupBase.h"
#include "PaintingState.h"
#include "Bitmap.h"
#include "BitmapEffect.h"

#define SD_PIN 53  // SD card CS pin

class BitmapEffectSetup : public EffectSetupBase
{
private:
	int m_current_file_index = 0;
	Bitmap m_current_bitmap;

	int frameDelay = 10;
	String *m_bitmap_filenames[255];
	uint16_t m_num_bitmaps = 0;

	BitmapEffect *m_effect;

	typedef struct
	{
		uint16_t previous_bitmap;
		uint16_t next_bitmap;
		uint16_t slower_frame;
		uint16_t faster_frame;
		uint16_t paint_button;
		uint16_t repeat_paint_toggle;
		uint16_t random_offset_toggle;
		uint16_t preview_button;
		uint16_t back_button;
		uint16_t go_button;
	} BitmapSelectionButtons;

	typedef struct
	{
		int back_button;
	} SdCardCancelButtons;

	bool setup_sdcard();
	void read_filenames_from_sdcard();
	int get_sdcard_filenames(File directory, int file_count);
	void clear_stored_files(bool free_allocated_bitmaps);

	void display_time_to_show_bitmap(uint32_t frame_delay, Bitmap bitmap);
	void display_frame_delay(uint32_t frame_delay);
	void display_repeat(BitmapSelectionButtons &buttons, boolean repeat);
	void display_random_offset(BitmapSelectionButtons &buttons, boolean random_offset);
	void display_current_bitmap(uint32_t x, uint32_t y, uint32_t display_width, uint32_t display_height);
	void retrieve_bitmap_details(String bitmap_filename);
	void initialise_sd_read_menu(SdCardCancelButtons &buttons);
	void initialise_main_interface(BitmapSelectionButtons &buttons);
	void setup_loop();
	void set_blank_bitmap_page();

public:
	String name();
	void engage();
	BitmapEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, BitmapEffect *effect);
};


#endif

