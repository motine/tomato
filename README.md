# Tomato LED Timer

This is a little project, which takes an Arduino and some parts and turns it into a timer.
See device usage below for details.

## Requirements

* See circuit for needed parts (Arduino (e.g. NanoV3), 2 buttons, Adafruit 8x8 BiColor Matrix with LED backpack).
* Install Adafruit_GFX, Adafruit_LEDBackpack libraries: https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix
* Install inotool (`brew install ino`) to compile and upload outside of Arduino.

## Device usage

	Press B1 short for advancing the minutes to be counted down.
	Press B1 long for resetting the minutes to 1.

## Resources
* [How to connect the LED Matrix](https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix#mini-8x8-matrix-software) (CL = SCL)
* [LED Backpack Reference](https://github.com/adafruit/Adafruit-LED-Backpack-Library/blob/master/Adafruit_LEDBackpack.h)
* [LED GFX Library tutorial](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives)
* [How to read resistors](http://elektronik-kurs.net/elektrotechnik/farbcode-toleranzen-normreihen-leistung/)
* [Resistor calculator](https://www.ph-ludwigsburg.de/html/2f-tech-s-01/studium/Veranstaltungsmaterial/Programme/Widerstand%20Farbcode%204%20und%205%20Ringe_DIN%2041429.htm)

Fix for upload error (Programmer not found)
http://stackoverflow.com/a/20735393