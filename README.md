## Synopsis

LEDStick_TFT is designed primarily for lightsticks based on Michael Ross' original tutorial (http://mrossphoto.com/digital-light-wand/), and the TFT concept was added by Justin Barkby (https://github.com/barkby/LEDStick)

We've taken the original concept and hooked it up to a Mega 2560, Sainsmart TFT shield, and Sainsmart TFT (TFT_320QVT). The TFT goes through UTFT so in theory any UTFT supported TFT's should be ok.

Input is via the touchscreen, though a GPIO pin can be used while painting to advance the state of the stick (Waiting->Painting->Not Painting-> Back to menu).

## Motivation

Basically wanted to get back into C++ coding and playing with Arduinos :)

## Installation

There are some 3rd party files for the TFT, Touch and buttons in the 3rd Party Libraries folder. Add these to your Arduino library. They're the latest versions, but UTFT needed tweaking for versions of the ITDB32S Sainsmart display (look in UTFT\tft_drivers\ssd1289).
These libraries can also be retrieved from http://www.rinkydinkelectronics.com

The AdaFruit NeoPixel library can be retrieved from the usual sources and included (https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation).

### Using the Arduino IDE:
* I've used Arduino IDE 1.5.8 and 1.8.1 for compile-testing
* File/Open and open LEDStick_TFT.ino - you'll see all the other files in the directory appear too.
* Verify/Upload and you should be good. If you want to try it without the stick added it'll still display details on the screen.

### Using Visual Studio (with the Arduino addin from http://www.visualmicro.com/)
* Open the LEDStick_TFT.sln file
* Set the appropriate COM port for the Arduino
* Select Build/Upload

In both cases if you need debug, the application sends diagnostics over the serial port.

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