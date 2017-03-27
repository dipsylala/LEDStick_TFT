## Synopsis

LEDStick_TFT is designed primarily for lightsticks based on Michael Ross' original tutorial (http://mrossphoto.com/digital-light-wand/), and the TFT concept was added by Justin Barkby (https://github.com/barkby/LEDStick)

We've taken the original concept and hooked it up to a Mega 2560, Sainsmart TFT shield, and Sainsmart TFT (TFT_320QVT). The TFT goes through UTFT so in theory any UTFT supported TFT's should be ok.

Input is via the touchscreen, though a GPIO pin can be used while painting to advance the state of the stick (Waiting->Painting->Not Painting-> Back to menu).

## Motivation

Basically wanted to get back into C++ coding and playing with Arduinos :)

## Installation

The AdaFruit NeoPixel library can be retrieved from the usual sources and included (https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation).

There are some 3rd party files for the TFT, Touch and buttons in the 3rd Party Libraries folder.

### Latest_UTFT_With_URTouch.zip - UTFT/URTouch/UTFT_Buttons
This set is the latest - it can also be retrieved from http://www.rinkydinkelectronics.com
### Sainsmart_UTFT_With_UTOUCH.zip - Includes UTFT/UTouch/UTFT_Buttons
This set is the a version I had supplied with some Sainsmart hardware. Sainsmart use a knock-off version of the original UTFT libraries.

By default LEDStick_TFT will use the UTouch libraries. If you have hardware capable of using the URTouch libraries, add the URTOUCH_USED preprocessor definition to your compilation parameters.


### Using the Arduino IDE:
* I've used Arduino IDE 1.5.8 and 1.8.1 for compile-testing
* File/Open and open LEDStick_TFT.ino - you'll see all the other files in the directory appear too.
* Verify/Upload and you should be good. If you want to try it without the stick added it'll still display details on the screen.

### Using Visual Studio (with the Arduino addin from http://www.visualmicro.com/)
* Open the LEDStick_TFT.sln file
* Set the appropriate COM port for the Arduino
* Select Build/Upload

In both cases if you need debug, the application sends diagnostics over the serial port.

## Troubleshooting
* Blank screen on startup
	If you're running a Sainsmart screen you might be running a slightly different variation. In the UTFT\tft_drivers\ssd1289\ library folder there are 2 files:
	* initlcd.h
	* initlcd.h.original

    Try deleting or renaming the initlcd.h to initlcd.h.new
    Then rename the initlcd.h.original to initlcd.h

* Selecting Solid/Fade causes the Arduino to reboot.
	There's a chance you're not supplying enough amperage to the Arduino/Stick
	* A Mega 2560 running the software draws approx 330mA
	* 20% brightness, 144 pixels showing white: 540mA
	* 9% brightness, 144 pixels showing white: 413mA
	
	If you're running this off a USB port it may not be able to support a higher amperage and things start rebooting.

## API Reference

I've made this extensible (mainly so I could test it, but I'm using this for a Teensy version that's controlled by bluetooth)

Look at SolidEffect.cpp, SolidEffect.h, SolidEffectSetup.cpp and SolidEffectSetup.h for a basic example.

Create a new effect? Add it in setup() in LEDStick_TFT.ino when we create the other effects and you should be golden.

Effects are disconnected from their Setups for a reason. I'll be porting this to different platforms. Currently porting to a Teensy controlled by Bluetooth. The effect remains the same, but the configuration comes via bluetooth and there's no touchscreen if you want to progress the LED effect. If that's the case, use a different StickHarware, and update your StateMachine to only look for GPIO pins. Simples.

## Contributors

More effects! :) Bitmaps are looking a little crowded now so maybe not more we can do there without introducing subscreens. 

Multiple bitmaps in one painting session, controllable by GPIO? Code is there, but looking at UI and how to control it mid-paint.

Read Fade configurations in a basic form from the SD card. Structure is already there in read_fades_from_source in FadeEffectSetup. JSON/XML read into the structure. 

If you wanted to, you could switch out the TFT and go back to LCD. The interface is held in MenuSelection.cpp and *Setup.cpp. Those essentially hold the UI.

Want to change the stick? Look in LEDStick.cpp - that's the wrapper around the NeoPixel so you could change it to be the wrapper for.... whatever.

## License

License is GPLv3. I'd like folks to contribute not steal. Make money from good support and selling the hardware, but not off this code.