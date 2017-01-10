// RGBController.h

#ifndef _RGBCONTROLLER_h
#define _RGBCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "StickHardware.h"

extern uint8_t arial_bold[];

class RGBController
{
private:

	StickHardware m_hardware;

	uint32_t m_xmin;
	uint32_t m_ymin;
	uint32_t m_xmax;
	uint32_t m_ymax;
	
public:
	void create_interface_components(StickHardware hardware, uint32_t x, uint32_t y);
	void check_point(uint32_t x, uint32_t y, RGB &rgb, boolean has_changed);
};


#endif

