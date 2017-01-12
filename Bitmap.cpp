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

#include "Bitmap.h"

uint32_t Bitmap::read_long_from_file(File dataFile)
{
	uint32_t retValue;
	byte incomingbyte;

	incomingbyte = read_byte_from_file(dataFile);
	retValue = (uint32_t)((byte)incomingbyte);

	incomingbyte = read_byte_from_file(dataFile);
	retValue += (uint32_t)((byte)incomingbyte) << 8;

	incomingbyte = read_byte_from_file(dataFile);
	retValue += (uint32_t)((byte)incomingbyte) << 16;

	incomingbyte = read_byte_from_file(dataFile);
	retValue += (uint32_t)((byte)incomingbyte) << 24;

	return retValue;
}

uint16_t Bitmap::read_int_from_file(File dataFile)
{
	byte incomingbyte;
	uint16_t retValue;

	incomingbyte = read_byte_from_file(dataFile);
	retValue = (uint16_t)((byte)incomingbyte);

	incomingbyte = read_byte_from_file(dataFile);
	retValue += (uint16_t)((byte)incomingbyte) << 8;

	return retValue;
}

int Bitmap::read_byte_from_file(File dataFile)
{
	int retbyte = -1;
	while (retbyte < 0)
	{
		retbyte = dataFile.read();
	}

	return retbyte;
}


int32_t Bitmap::read_bitmap_info(File bitmap_file)
{
	filename = bitmap_file.name();

	bitmap_file.seek(0);
	bitmap_info.bmpType = read_int_from_file(bitmap_file);
	bitmap_info.bmpSize = read_long_from_file(bitmap_file);
	bitmap_info.bmpReserved1 = read_int_from_file(bitmap_file);
	bitmap_info.bmpReserved2 = read_int_from_file(bitmap_file);
	bitmap_info.bmpOffBits = read_long_from_file(bitmap_file);
	bitmap_info.imgSize = read_long_from_file(bitmap_file);
	bitmap_info.imgWidth = read_long_from_file(bitmap_file);
	bitmap_info.imgHeight = read_long_from_file(bitmap_file);
	bitmap_info.imgPlanes = read_int_from_file(bitmap_file);
	bitmap_info.imgBitCount = read_int_from_file(bitmap_file);
	bitmap_info.imgCompression = read_long_from_file(bitmap_file);
	bitmap_info.imgSizeImage = read_long_from_file(bitmap_file);
	bitmap_info.imgXPelsPerMeter = read_long_from_file(bitmap_file);
	bitmap_info.imgYPelsPerMeter = read_long_from_file(bitmap_file);
	bitmap_info.imgClrUsed = read_long_from_file(bitmap_file);
	bitmap_info.imgClrImportant = read_long_from_file(bitmap_file);

	if (validate_is_bitmap(&bitmap_info) == false)
	{
		return BMP_INVALID_FILE;
	}

	// BMP rows are padded (if needed) to 4-byte boundary
	bitmap_info.line_length_in_bytes = (bitmap_info.imgWidth * 3 + 3) & ~3;

	return BMP_VALID;
}

boolean Bitmap::validate_is_bitmap(BitmapInfo *bitmap_info)
{
	if (bitmap_info->bmpType != BMP_BF_TYPE || bitmap_info->bmpOffBits != BMP_BF_OFF_BITS)
	{
		return false;
	}

	return true;
}

boolean Bitmap::validate_is_supported_bitmap(BitmapInfo *bitmap_info)
{
	if (bitmap_info->imgSize != BMP_BI_SIZE 
		|| bitmap_info->imgWidth <= 0 
		|| bitmap_info->imgHeight <= 0
		|| bitmap_info->imgPlanes != 1
		|| bitmap_info->imgBitCount != 24
		|| bitmap_info->imgCompression != BMP_BI_RGB
		|| bitmap_info->imgSizeImage == 0)
	{
		return false;
	}

	return true;
}

void Bitmap::read_image_line(File bitmap_file, uint32_t line_number, RGB*rgb_line, uint32_t rgb_length)
{
	uint32_t read_length = rgb_length < bitmap_info.imgWidth ? rgb_length : bitmap_info.imgWidth;

	for (int x = 0; x < read_length; x++)
	{
		uint32_t offset = (BMP_BF_OFF_BITS + ((line_number * bitmap_info.line_length_in_bytes) + (x * 3)));

		bitmap_file.seek(offset);

		rgb_line[x].blue = pgm_read_byte(&gammaTable[read_byte_from_file(bitmap_file)]);
		rgb_line[x].green = pgm_read_byte(&gammaTable[read_byte_from_file(bitmap_file)]);
		rgb_line[x].red = pgm_read_byte(&gammaTable[read_byte_from_file(bitmap_file)]);
	}
}

inline byte Bitmap::gamma(byte x)
{
	return gammaTable[x];
}


// Gamma correction (grabbed from https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix )
// Note that this still runs 0-255. If we need to do LED-specific
// correction (eg 7 bit colorspace rather than 8) then do that
// in the driver itself

const uint8_t PROGMEM Bitmap::gammaTable[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };