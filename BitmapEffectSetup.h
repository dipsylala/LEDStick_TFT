// BitmapProcessor.h

#ifndef _BITMAPPROCESSOR_h
#define _BITMAPPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>
#include <SPI.h>
#include "BaseEffectSetup.h"
#include "PaintingState.h"
#include "Bitmap.h"
#include "BitmapEffect.h"

#define SD_PIN 53  // SD card CS pin

class BitmapEffectSetup : public BaseEffectSetup
{
private:
	int m_current_file_index = 0;
	Bitmap m_current_bitmap;

	int frameDelay = 10;
	String *m_bitmap_filenames[255];
	int m_num_bitmaps = 0;

	BitmapEffect *m_effect;

	typedef struct
	{
		int previous_bitmap;
		int next_bitmap;
		int slower_frame;
		int faster_frame;
		int paint_button;
		int repeat_paint_toggle;
		int back_button;
		int go_button;
	} BitmapSelectionButtons;

	typedef struct
	{
		int back_button;
	} SdCardCancelButtons;

	bool setup_sdcard();
	void read_filenames_from_sdcard();
	int get_sdcard_filenames(File directory, int file_count);
	void clear_stored_files(bool free_allocated_bitmaps);

	void calculate_time_to_display(uint32_t frame_delay, Bitmap bitmap);
	void display_frame_delay(uint32_t frame_delay);
	void display_repeat(BitmapSelectionButtons &buttons, boolean repeat);
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

