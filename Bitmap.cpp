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

// Calculation retrieved from https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix 
void Bitmap::set_gamma(float gamma_level)
{
	for (int i = 0; i <= 255; i++) {
		gammaTable[i] = (int)(pow((float)i / (float)255, gamma_level) * 255 + 0.5);
	}
}

void Bitmap::read_image_line(File bitmap_file, uint32_t line_number, RGB*rgb_line, uint32_t rgb_length)
{
	uint32_t read_length = rgb_length < bitmap_info.imgWidth ? rgb_length : bitmap_info.imgWidth;

	for (int x = 0; x < read_length; x++)
	{
		uint32_t offset = (BMP_BF_OFF_BITS + ((line_number * bitmap_info.line_length_in_bytes) + (x * 3)));

		bitmap_file.seek(offset);

		rgb_line[x].blue = gammaTable[read_byte_from_file(bitmap_file)];
		rgb_line[x].green = gammaTable[read_byte_from_file(bitmap_file)];
		rgb_line[x].red = gammaTable[read_byte_from_file(bitmap_file)];
	}
}