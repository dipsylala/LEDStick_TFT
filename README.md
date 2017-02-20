## Synopsis

LEDStick_TFT is designed primarily for lightsticks based on Michael Ross' original tutorial (http://mrossphoto.com/digital-light-wand/), and TFT concept was added by Justin Barkby (https://github.com/barkby/LEDStick)

We've taken the original concept and hooked it up to a Mega 2560, Sainsmart TFT shield, and Sainsmart TFT (TFT_320QVT). The TFT goes through UTFT so in theory any UTFT supported TFT's should be ok.

Input is via the touchscreen, though a GPIO pin can be used while painting to advance the state of the stick (Waiting->Painting->Not Painting-> Back to menu).

## Motivation

Basically wanted to get back into C++ coding and playing with Arduinos :)

## Installation

I've been testing under 1.5 - mainly because it's more convenient for the hardware I've got (mental note to avoid Sainsmart next time). Compiles under 1.8 but the SD card doesn't work.

There are some 3rd party files for the TFT, SD Card and Touch in the 3rd Party Libraries folder. Add these to your Arduino library.

The AdaFruit NeoPixel library can be retrieved from the usual sources and included. It can be the latest one.

Using the Arduino IDE:
* File/Open and open LEDStick_TFT.ino - you'll see all the other files in the directory appear too.
* Verify/Upload and you should be good. If you want to try it without the stick added it'll still display details on the screen.

Using Visual Studio (with the Arduino addin from http://www.visualmicro.com/)
* Open the LEDStick_TFT.sln file
* Select Build/Upload


## API Reference

I've made this extensible (mainly so I could test it, but I'm using this for a Teensy version that's controlled by bluetooth')

Look at SolidEffect.cpp, SolidEffect.h, SolidEffectSetup.cpp and SolidEffectSetup.h for a basic example.

Create a new effect? Add it in setup() in LEDStick_TFT.ino when we create the other effects and you should be golden.

Effects are disconnected from their Setups for a reason. I'll be porting this to different platforms. Currently porting to a Teensy controlled by Bluetooth. The effect remains the same, but the configuration comes via bluetooth and there's no touchscreen if you want to progress the LED effect. If that's the case, use a different StickHarware, and update your StateMachine to only look for GPIO pins. Simples.

## Contributors

More effects! :) Bitmaps are looking a little crowded now so maybe not more we can do there without introducing subscreens. 

Multiple bitmaps in one painting session, controllable by GPIO? Code is there, but looking at UI and how to control it mid-paint.

Read Fades in a basic form from the SD card. Structure already there in read_fades_from_source in FadeEffectSetup. JSON/XML read into the structure. 

If you wanted to, you could switch out the TFT and go back to LCD. The interface is held in MenuSelection.cpp and *Setup.cpp. Those essentially hold the UI.

Want to change the stick? Look in LEDStick.cpp - that's the wrapper around the NeoPixel so you could change it to be the wrapper for.... whatever.

## License

License is GPLv3. I'd like folks to contribute not steal. Make money from good support and selling the hardware, but not off this code.