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

// Credit where credit's due
// Ideas and concepts from LEDStick by Justin Barkby who created a
// TFT-based version of Michael Ross' code (http://mrossphoto.com/)

#if defined(__AVR__)
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <UTFT.h>
#include <SD.h>
#include <EEPROM.h>
#include <SPI.h>
#include <memorysaver.h>
#include <TFT.h>
#include <FastLED.h>
#include "FadeBase.h"
#include "FadeConfiguration.h"
#include "LEDStick.h"
#include "BitmapEffect.h"
#include "StarEffect.h"
#include "FadeEffect.h"
#include "SolidEffect.h"
#include "Configurationmanager.h"
#include "EepromConfiguration.h"
#include "BitmapInfo.h"
#include "Bitmap.h"
#include "PaintingState.h"
#include "PaintingStateMachine.h"
#include "StarEffectSetup.h"
#include "SolidEffectSetup.h"
#include "LEDRGB.h"
#include "RGBController.h"
#include "MenuSelection.h"
#include "FadeEffectSetup.h"
#include "BitmapEffectSetup.h"
#include "EffectSetupBase.h"
#include "StickHardware.h"

#define imagedatatype  unsigned int
#elif defined(__PIC32MX__)
#define imagedatatype  unsigned short
#elif defined(__arm__)
#define imagedatatype  unsigned short
#endif

extern uint8_t SmallFont[];
extern uint8_t arial_bold[];
extern uint8_t Various_Symbols_32x32[];

UTFT tft(ITDB32S, 38, 39, 40, 41);
UTouch  touch(6, 5, 4, 3, 2);
UTFT_Buttons buttons(&tft, &touch);
LEDStick *stick;
MenuSelection *menu_selection;

uint32_t m_num_effects = 0;
EffectSetupBase **m_effects;

void setup()
{
	StickHardware hardware;
	Serial.begin(115200);

	EepromConfiguration configuration;
	ConfigurationData config_data = configuration.read_configuration();

	hardware.pStrip = new LEDStick(config_data.num_pixels);
	hardware.pTft = &tft;
	hardware.pTft->InitLCD();
	hardware.pTft->clrScr();
	hardware.pTft->setFont(arial_bold);

	hardware.pTouch = &touch;
	hardware.pTouch->InitTouch(LANDSCAPE);
	hardware.pTouch->setPrecision(PREC_HI);

	hardware.pButtons = &buttons;
	hardware.pButtons->setSymbolFont(Various_Symbols_32x32);

	intro_message(hardware);
	delay(1000);

	PaintingStateMachine state_machine(hardware);

	m_num_effects = 4;
	m_effects = new EffectSetupBase*[m_num_effects];
	m_effects[0] = new SolidEffectSetup(hardware, &state_machine, new SolidEffect(&state_machine, hardware.pStrip));
	m_effects[1] = new FadeEffectSetup(hardware, &state_machine, new FadeEffect(&state_machine, hardware.pStrip));
	m_effects[2] = new BitmapEffectSetup(hardware, &state_machine, new BitmapEffect(&state_machine, hardware.pStrip));
	m_effects[3] = new StarEffectSetup(hardware, &state_machine, new StarEffect(&state_machine, hardware.pStrip));

	ConfigurationManager *configuration_manager = new ConfigurationManager(hardware);

	menu_selection = new MenuSelection(hardware, m_effects, m_num_effects, configuration_manager);
	menu_selection->run();

	//for (uint32_t i = 0; i < num_effects; i++)
	//{
	//	delete effects[i];
	//}

	//delete effects;
}

void loop()
{
	menu_selection->loop();

	for (uint32_t i = 0; i < m_num_effects; i++)
	{
		m_effects[i]->loop();
	}
}

void intro_message(StickHardware hardware)
{
	hardware.pTft->setFont(arial_bold);
	hardware.pTft->setBackColor(0, 0, 0);
	hardware.pTft->print("LED Stick", CENTER, 0);
	hardware.pTft->setFont(SmallFont);
	hardware.pTft->print("Digital LightStick v0.10 BETA", CENTER, 16);
	hardware.pTft->print("by Justin Barkby", CENTER, 50);
	hardware.pTft->print("(and a little by Cus)", CENTER, 70);
}


