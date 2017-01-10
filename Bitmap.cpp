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
	retValue += (uint16_t)((byte)incomingbyte);

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

	uint32_t line_length_in_bytes = bitmap_info.imgWidth * 3; // 3 because of R,G,B values

	if (validate_is_bitmap(&bitmap_info) == false)
	{
		return BMP_INVALID_FILE;
	}

	if ((line_length_in_bytes % 4) != 0)
	{
		bitmap_info.line_length_in_bytes = (line_length_in_bytes / 4 + 1) * 4;
	}
	else
	{
		bitmap_info.line_length_in_bytes = line_length_in_bytes;
	}
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

void Bitmap::read_image_line(File bitmap_file, uint32_t line_number, RGB*rgb_line, int32_t rgb_length)
{
	uint32_t read_length = rgb_length < bitmap_info.imgWidth ? rgb_length : bitmap_info.imgWidth;

	for (int x = 0; x < read_length; x++)
	{
		uint32_t offset = (BMP_BF_OFF_BITS + ((line_number * bitmap_info.line_length_in_bytes) + (x * 3)));

		bitmap_file.seek(offset);

		rgb_line[x].blue = gamma(read_byte_from_file(bitmap_file));
		rgb_line[x].green = gamma(read_byte_from_file(bitmap_file));
		rgb_line[x].red = gamma(read_byte_from_file(bitmap_file));
	}
}

inline byte Bitmap::gamma(byte x)
{
	return x;
	//return pgm_read_byte(&gammaTable[x]);
}


// Gamma correction compensates for our eyes' nonlinear perception of
// intensity.  It's the LAST step before a pixel value is stored, and
// allows intermediate rendering/processing to occur in linear space.
// The table contains 256 elements (8 bit input), though the outputs are
// only 7 bits (0 to 127).  This is normal and intentional by design: it
// allows all the rendering code to operate in the more familiar unsigned
// 8-bit colorspace (used in a lot of existing graphics code), and better
// preserves accuracy where repeated color blending operations occur.
// Only the final end product is converted to 7 bits, the native format
// for the LPD8806 LED driver.  Gamma correction and 7-bit decimation
// thus occur in a single operation.
const uint8_t Bitmap::gammaTable[] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,
	2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,
	4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,
	7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 10, 10, 11,
	11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
	16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
	23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
	30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
	40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
	50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
	62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
	76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
	92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
	109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127
};