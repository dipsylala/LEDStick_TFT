// FadeEffectSetup.h

#ifndef _FadeEffectSetup_h
#define _FadeEffectSetup_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseEffectSetup.h"
#include "PaintingState.h"
#include "FadeConfiguration.h"
#include "FadeBase.h"
#include "FadeEffect.h"

class FadeEffectSetup : public BaseEffectSetup, FadeBase
{
private:
	typedef struct
	{
		int slower_button;
		int faster_button;
		int previous_config;
		int next_config;
		int back_button;
		int go_button;
	} FadeSelectionButtons;

	FadeSelectionButtons m_fade_selection_buttons;
	FadeEffect *m_effect;

	int read_fades_from_source(FadeConfiguration **fade_configuration);
	void initialise_main_interface(FadeSelectionButtons &buttons);
	void set_selected_configuration(FadeConfiguration &fade_configuration);
	void show_current_delay(uint32_t delay);
	void setup_loop();

public:
	String name();
	void engage();
	FadeEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, FadeEffect *effect);
};


#endif

