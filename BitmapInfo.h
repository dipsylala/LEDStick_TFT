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

