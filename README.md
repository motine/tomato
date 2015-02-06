# Tomato LED Timer

This is a little project, which takes an Arduino and some parts and turns it into a timer.
See device usage below for details.

![final timer](https://raw.github.com/motine/tomato/master/final.jpg)

## Parts and circuit

I bought the following electronic parts:

* Arduino [Nano](http://arduino.cc/en/Main/arduinoBoardNano) V3 (I got mine from SainSmart)
* Adafruit [8x8 BiColor Matrix](http://www.adafruit.com/product/902) with LED backpack
* 2 buttons and some cables

I uploaded a pdf with the circuit in the repo.

To compile the code you need the `Adafruit_GFX` and `Adafruit_LEDBackpack` libraries from [here](https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix).

## Timer usage

This display shows the minute pattern (0 - 9 minutes) on the right **lower corner**. The outer rings show **10 minute steps**.

There are 4 modes:

* **Setting** You can use B1 (button 1) to add minutes to the count down. Each press **adds 5 minutes**. Use B2 to start the countdown.
* **Countdown** The timer runs. You can press any button to switch the timer off.
* **Alarm** BAAAAM, stop what you are doing! Press any key to go into overtime.
* **Overtime** This mode shows how many minutes have passed since the alarm. Press any key to switch the alarm off.
* **Off** Power safe. Press any key for half a second to bring the alarm to life.

See the video on [youtube](http://youtu.be/PVaG_D6qm80) (100x faster).

## The casing a.k.a. box

I made the `box.svg` with OmniGraffle and then printed it at the [FabLab Berlin](www.fablab-berlin.org) with their laser cutter. I used 3mm MDF.
They use the software [Visicut](http://hci.rwth-aachen.de/visicut) to import the SVG and drive the cutter. Please also see the PDF for some annotations.

Remember (this is mostly for me, so I don't forget):

* Add add some more material to the male parts to compensate for the laser cutting stuff away.
* Before importing in Visicut, check for duplicate paths in your SVG (e.g. with Inkscape or illustrator)
* Don't add backgrounds to the shapes you want to cut out. This may lead to duplicate paths (blurs the lasered edge).
* Remove the Border path around the canvas.
* Calibrate the cutter.

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
