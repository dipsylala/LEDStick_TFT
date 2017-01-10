// SolidProcessor.h

#ifndef _SOLIDPROCESSOR_h
#define _SOLIDPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "BaseEffectSetup.h"
#include "RGBController.h"
#include "PaintingState.h"
#include "SolidEffect.h"

class SolidEffectSetup : public BaseEffectSetup
{
private:
	typedef struct
	{
		int back_button;
		int go_button;
	} SolidSelectionButtons;

	void initialise_main_interface(SolidSelectionButtons &buttons);
	void setup_loop ();

	RGBController rgbController;
	SolidEffect *m_effect;

public:
	String name();
	void engage();
	SolidEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, SolidEffect *effect);
};

#endif

