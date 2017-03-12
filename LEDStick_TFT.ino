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
#include <URTouchCD.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>
#include <UTFT.h>
#include <SD.h>
#include <EEPROM.h>
#include <SPI.h>
#include <memorysaver.h>
#include <Adafruit_NeoPixel.h>
#include "FadeBase.h"
#include "FadeConfiguration.h"
#include "LEDStick.h"
#include "LengthConfigurationmanager.h"
#include "BrightnessConfigurationmanager.h"
#include "EepromConfiguration.h"
#include "BitmapInfo.h"
#include "Bitmap.h"
#include "PaintingState.h"
#include "PaintingStateMachine.h"
#include "RGB.h"
#include "RGBController.h"
#include "MenuSelection.h"
#include "BitmapEffect.h"
#include "StarEffect.h"
#include "FadeEffect.h"
#include "SolidEffect.h"
#include "FadeEffectSetup.h"
#include "BitmapEffectSetup.h"
#include "StarEffectSetup.h"
#include "SolidEffectSetup.h"
#include "ChaseEffectSetup.h"
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
URTouch  touch(6, 5, 4, 3, 2);
UTFT_Buttons buttons (&tft, &touch);

LEDStick *stick;
StickHardware hardware;

void intro_message(StickHardware hardware)
{
	hardware.pTft->setFont(arial_bold);
	hardware.pTft->setBackColor(0, 0, 0);
	hardware.pTft->print(String("LED Stick"), CENTER, 0);
	hardware.pTft->setFont(SmallFont);
	hardware.pTft->print(String("Digital LightStick v0.10 BETA"), CENTER, 16);
	hardware.pTft->print(String("by Justin Barkby and Cus"), CENTER, 50);
}

void setup()
{
	Serial.begin(115200);

	Serial.println("Initialising Screen");
	tft.InitLCD(LANDSCAPE);
	Serial.println("UTFT Version: " + String (UTFT_VERSION));
  
	Serial.println("Initialising Touch");
	hardware.pTouch = &touch;
	hardware.pTouch->InitTouch(LANDSCAPE);
	hardware.pTouch->setPrecision(PREC_HI);

	Serial.println("Creating Buttons");
	Serial.println("UTFT Buttons Version: " + String (UTFT_BUTTONS_VERSION));

	Serial.println("Retrieving Configuration");

	EepromConfiguration configuration;
	ConfigurationData config_data = configuration.read_configuration();

	Serial.println("Initialising LEDStick");

	hardware.pStrip = new LEDStick(config_data.num_pixels);
	hardware.pTft = &tft;
	hardware.pTft->InitLCD();
	hardware.pTft->clrScr();
	hardware.pTft->setFont(arial_bold);

	hardware.pButtons = &buttons;
	hardware.pButtons->setSymbolFont(Various_Symbols_32x32);

	intro_message(hardware);
	delay(1000);
}

void loop()
{
	PaintingStateMachine state_machine(hardware);

	int num_effects = 5;
	EffectSetupBase **effects = new EffectSetupBase*[num_effects];
	effects[0] = new SolidEffectSetup(hardware, &state_machine, new SolidEffect(&state_machine, hardware.pStrip));
	effects[1] = new FadeEffectSetup(hardware, &state_machine, new FadeEffect(&state_machine, hardware.pStrip));
	effects[2] = new BitmapEffectSetup(hardware, &state_machine, new BitmapEffect(&state_machine, hardware.pStrip));
	effects[3] = new StarEffectSetup(hardware, &state_machine, new StarEffect(&state_machine, hardware.pStrip));
	effects[4] = new ChaseEffectSetup(hardware, &state_machine, new ChaseEffect(&state_machine, hardware.pStrip));

	LengthConfigurationManager *length_configuration_manager = new LengthConfigurationManager(hardware);
	BrightnessConfigurationManager *brightness_configuration_manager = new BrightnessConfigurationManager(hardware);

	MenuSelection *menu_selection = new MenuSelection(hardware, effects, num_effects, length_configuration_manager, brightness_configuration_manager);
	menu_selection->run();

	for (uint32_t i = 0; i < num_effects; i++)
	{
		delete effects[i];
	}

	delete *effects;
}

