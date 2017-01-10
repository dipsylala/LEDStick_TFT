/*
LEDStick by  Justin Barkby

Original code by Michael Ross (http://mrossphoto.com/wordpress32/)
Modified from LCD to TFT touchscreen including a couple of features by Justin Barkby
Refactored and rewritten by Marcus Watson

*/

//TODO: 
// Eventually refactor to remove configuration from the effect loop. 
//   Use DI to inject configuration into each Effect Processor so we 
//   can have different ways of configuring (LCD/TFT/Bluetooth)

#if defined(__AVR__)
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <UTFT.h>
#include <SD.h>
#include <EEPROM.h>
#include <SPI.h>
#include <memorysaver.h>
#include <Adafruit_NeoPixel.h>
#include <TFT.h>
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
#include "RGB.h"
#include "RGBController.h"
#include "MenuSelection.h"
#include "FadeEffectSetup.h"
#include "BitmapEffectSetup.h"
#include "BaseEffectSetup.h"
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

	int num_processors = 4;
	BaseEffectSetup **processors = new BaseEffectSetup*[num_processors];
	processors[0] = new SolidEffectSetup(hardware, &state_machine, new SolidEffect(&state_machine, hardware.pStrip));
	processors[1] = new FadeEffectSetup(hardware, &state_machine, new FadeEffect(&state_machine, hardware.pStrip));
	processors[2] = new BitmapEffectSetup(hardware, &state_machine, new BitmapEffect(&state_machine, hardware.pStrip));
	processors[3] = new StarEffectSetup(hardware, &state_machine, new StarEffect(&state_machine, hardware.pStrip));

	ConfigurationManager *configuration_manager = new ConfigurationManager(hardware);

	MenuSelection *menu_selection = new MenuSelection(hardware, processors, num_processors, configuration_manager);
	menu_selection->run();

}

void loop()
{

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


