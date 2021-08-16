## Introduction
csound-jstick was created in response to the builtin joystick opcode being a bit inefficient and not ideal to use. This attempts to make it a bit easier by presenting the output in two arrays (buttons and axes). A maximum of 4 axes and 12 buttons is supported.
The opcode uses evdev so only works on Linux.


## Requirements
 - Csound development libraries
 - Cmake 2.8.12 or later


## Building
Create a build directory at the top of the source tree, execute *cmake ..*, *make* and optionally *make install* as root. If the latter is not used/possible then the resulting module can be used with the *--opcode-lib* flag in Csound. eg:
	
	cd csound-jstick
	mkdir build && cd build
	cmake ..
	make && sudo make install


## Opcode overview
### jstick 
*kaxes[] kbuttons[] jstick inum*

Obtain joystick data at k-rate.

 - kaxes[] : array containing axis data normalised to between 0 and 1, size is 4
 - kbuttons[] : array containing button data normalised to between 0 and 1, size is 12
 - inum : the joystick number corresponding to /dev/input

