## Synopsis

LEDStick_TFT is designed primarily for lightsticks based on Michael Ross' original tutorial (http://mrossphoto.com/digital-light-wand/)

We've taken the original concept and hooked it up to a Mega 2560, Sainsmart TFT shield, and Sainsmart TFT (TFT_320QVT). The TFT goes through UTFT so in theory any UTFT supported TFT's should be ok.

Input is via the touchscreen, though a GPIO pin can be used while painting to advance the state of the stick (Waiting->Painting->Not Painting-> Back to menu).

## Motivation

Basically wanted to get back into C++ coding and playing with Arduinos :)

## Installation

I've been testing under 1.5 - mainly because it's more convenient for the hardware I've got (mental note to avoid Sainsmart next time). Compiles under 1.8 but the SD card doesn't work.

Chuck it into Visual Studio/Arduino IDE, compile, upload.

## API Reference

I've made this extensible (mainly so I could test it, but I'm using this for a Teensy version that's controlled by bluetooth')

Look at SolidEffect.cpp, SolidEffect.h, SolidEffectSetup.cpp and SolidEffectSetup.h for a basic example.

Create a new effect? Add it in setup() in LEDStick_TFT.ino when we create the other effects and you should be golden.

## Contributors

Let people know how they can dive into the project, include important links to things like issue trackers, irc, twitter accounts if applicable.

## License

License is GPLv3. I'd like folks to contribute not steal. Make money from good support and selling the hardware, but not off this code.