# Tomato LED Timer

This is a little project, which takes an Arduino and some parts and turns it into a timer.
See device usage below for details.

## Requirements

* See circuit for needed parts (Arduino (e.g. NanoV3), 2 buttons, Adafruit 8x8 BiColor Matrix with LED backpack).
* Install Adafruit_GFX, Adafruit_LEDBackpack libraries: See [here](https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix).

## Timer usage

This display shows the minute pattern (0 - 9 minutes) on the left lower corner. The outer rings show 10 minute steps.

There are 4 modes:

* Setting: You can use B1 to add minutes to the count down. Each press adds 5 minutes. Use B2 to start the countdown.
* Countdown: The timer runs. You can press any button to switch the timer off.
* Alarm: BAAAAM, stop what you are doing! Press any key to go into overtime.
* Overtime: This mode shows how many minutes have passed since the alarm. Press any key to switch the alarm off.
* Off: Powersafe. Press any key for half a second to bring the alarm to life.

See a demo video on [youtube](http://youtu.be/PVaG_D6qm80) (100x faster):

<iframe width="560" height="315" src="//www.youtube.com/embed/PVaG_D6qm80" frameborder="0" allowfullscreen></iframe>

## Resources

* [How to connect the LED Matrix](https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix#mini-8x8-matrix-software) (CL = SCL)
* [Arduino Reference](http://arduino.cc/en/Reference/HomePage)
* [LED Backpack Reference](https://github.com/adafruit/Adafruit-LED-Backpack-Library/blob/master/Adafruit_LEDBackpack.h)
* [LED GFX Library on Github](https://github.com/adafruit/Adafruit-GFX-Library)
* [LED GFX Library tutorial](https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives)
* [How to read resistors](http://elektronik-kurs.net/elektrotechnik/farbcode-toleranzen-normreihen-leistung/)
* [Resistor calculator](https://www.ph-ludwigsburg.de/html/2f-tech-s-01/studium/Veranstaltungsmaterial/Programme/Widerstand%20Farbcode%204%20und%205%20Ringe_DIN%2041429.htm)

## Known issues

With the Arduino Nano, find [the fix](http://stackoverflow.com/a/20735393) for the `Programmer not found` error.