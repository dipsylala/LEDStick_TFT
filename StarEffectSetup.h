// StarProcessor.h

#ifndef _STARPROCESSOR_h
#define _STARPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseEffectSetup.h"
#include "PaintingState.h"
#include "RGBController.h"
#include "StarEffect.h"

class StarEffectSetup : public BaseEffectSetup
{
private:
	typedef struct
	{
		int gap_time_slower;
		int gap_time_faster;
		int star_time_slower;
		int star_time_faster;
		int back_button;
		int go_button;
	} StarSelectionButtons;

	StarSelectionButtons m_star_selection_buttons;
	StarEffect *m_effect;

	void initialise_main_interface(StarSelectionButtons &buttons);
	void setup_loop();

public:
	String name();
	void engage();
	StarEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, StarEffect *effect);
};

#endif

