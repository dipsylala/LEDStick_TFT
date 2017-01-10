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
		uint32_t slower_button;
		uint32_t faster_button;
		uint32_t steps_minus;
		uint32_t steps_plus;
		uint32_t previous_config;
		uint32_t next_config;
		uint32_t back_button;
		uint32_t go_button;
	} FadeSelectionButtons;

	FadeSelectionButtons m_fade_selection_buttons;
	FadeEffect *m_effect;

	int read_fades_from_source(FadeConfiguration **fade_configuration);
	void initialise_main_interface(FadeSelectionButtons &buttons);
	void set_selected_configuration(FadeConfiguration &fade_configuration);
	void show_current_delay(uint32_t delay);
	void show_current_steps(uint32_t steps);
	void setup_loop();

public:
	String name();
	void engage();
	FadeEffectSetup(StickHardware hardware, PaintingStateMachine *state_machine, FadeEffect *effect);
};


#endif

