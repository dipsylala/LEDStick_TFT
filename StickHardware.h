// StickHardware.h

#ifndef _STICKHARDWARE_h
#define _STICKHARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <UTFT.h>
#include <UTouch.h>	
#include <UTFT_Buttons.h>
#include "LEDStick.h"

class StickHardware
{
public:
	LEDStick *pStrip;
	UTFT *pTft;
	UTouch *pTouch;
	UTFT_Buttons *pButtons;
};


#endif

