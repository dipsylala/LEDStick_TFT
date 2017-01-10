// BitmapInfo.h

#ifndef _BITMAPINFO_h
#define _BITMAPINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
typedef struct
{
	uint16_t bmpType;
	uint32_t bmpSize;
	uint16_t bmpReserved1;
	uint16_t bmpReserved2;
	uint32_t bmpOffBits;
	uint32_t imgSize;
	uint32_t imgWidth;
	uint32_t imgHeight;
	uint16_t imgPlanes;
	uint16_t imgBitCount;
	uint32_t imgCompression;
	uint32_t imgSizeImage;
	uint32_t imgXPelsPerMeter;
	uint32_t imgYPelsPerMeter;
	uint32_t imgClrUsed;
	uint32_t imgClrImportant;

	uint32_t line_length_in_bytes;
} BitmapInfo;


#endif

