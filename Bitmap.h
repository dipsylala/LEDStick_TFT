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

#ifndef _BITMAP_h
#define _BITMAP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SD.h>

#include "BitmapInfo.h"
#include "RGB.h"

#define BMP_BF_OFF_BITS 54
#define BMP_BI_SIZE 40
#define BMP_BF_TYPE 0x4D42
#define BMP_BI_RGB  0L

#define BMP_VALID 0
#define BMP_INVALID_FILE -1
#define BMP_INVALID_BMP_FORMAT -2

class Bitmap
{
 protected:
	 static PROGMEM const uint8_t gammaTable[256];

	 uint32_t read_long_from_file(File dataFile);
	 uint16_t read_int_from_file(File dataFile);
	 int read_byte_from_file(File dataFile);
	 inline byte gamma(byte x);
	 boolean validate_is_bitmap(BitmapInfo *bitmap_info);
	 boolean validate_is_supported_bitmap(BitmapInfo *bitmap_info);
	 
 public:

	 BitmapInfo bitmap_info;

	 String filename;
	 int32_t read_bitmap_info(File bitmap_file);
	 void read_image_line(File bitmap_file, uint32_t line_number, RGB*rgb_line, uint32_t rgb_length);
};


#endif

