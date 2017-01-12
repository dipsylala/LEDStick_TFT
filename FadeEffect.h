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

#ifndef _FADEEFFECT_h
#define _FADEEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RGB.h"
#include "FadeConfiguration.h"
#include "LEDStick.h"
#include "PaintingStateMachine.h"
#include "FadeBase.h"

class FadeEffect : FadeBase
{
private:
	LEDStick *m_strip;
	PaintingStateMachine *m_state_machine;

public:
	void start_painting(FadeConfiguration &fade_configuration, uint32_t pulse_delay, uint32_t steps_between_colours);
	FadeEffect(PaintingStateMachine * state_machine, LEDStick * pStrip);
};

#endif

