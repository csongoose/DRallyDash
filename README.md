# DRallyDash
A fun arduino dashboard project with dirt rally

## Current version:
1.0.0

## How does it work?
The data is from the built-in telemetry the game provides. The python code takes the data, processes it and sends a message accordingly over serial.
The arduino processes the message and acts by turning its outputs either high or low. The outputs are in BCD format and can be processed by a BCD-7 segment chip (cd4543b or similar).
The RPM LEDs are direct outputs, so they need a resistor if the arduino is used with a 5v output.

## Pinout:

Arduino pin|Function
---|---
0|unused - reserved for serial
1|unused - reserved for serial
2|3rd digit D (2³)
3|3rd digit C (2²)
4|3rd digit B (2¹)
5|3rd digit A (2⁰)
6|2nd digit D (2³)
7|2nd digit C (2²)
8|2nd digit B (2¹)
9|2nd digit A (2⁰)
10|1st digit D (2³)
11|1st digit C (2²)
12|1st digit B (2¹)
13|1st digit A (2⁰)
A0 or 14|1st RPM led
A1 or 15|2nd RPM led
A2 or 16|3rd RPM led
A3 or 17|4th RPM led (max/shift NOW led)

## Changelog
### Version 1.0.0
* Initial release
* Supports a 3 digit 7 segment display with BCD to 7 segment chips
* Supports 4 RPM/shift helper LEDs

## Q&A

### What is it used for?
It is used for my current setup playing dirt rally 2.0.

### Why is it better than XY software?
It isn't. I am only eyperimenting with this.
