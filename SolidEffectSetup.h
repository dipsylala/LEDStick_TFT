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

#ifndef _SOLIDPROCESSOR_h
#define _SOLIDPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "EffectSetupBase.h"
#include "RGBController.h"
#include "SolidEffect.h"

class SolidEffectSetup : public EffectSetupBase
{
private:
	typedef struct
	{
		int back_button;
		int go_button;
	} SolidSelectionButtons;

	void initialise_main_interface(SolidSelectionButtons &buttons);
	void setup_loop () override;

	RGBController rgbController;
	SolidEffect *m_effect;

public:
	String name() override;
	void engage() override;
	SolidEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, SolidEffect *effect);
};

#endif

