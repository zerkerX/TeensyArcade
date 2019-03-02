This repository is for the firmware for a Teensy LC-powered Arcade Stick. This project uses the [MSF-XINPUT](https://github.com/zlittell/MSF-XINPUT) library by Zachery Littell for XInput protocol support and locally written code for mappings and SNES/NES support. Until the parent version is fully updated to support Teensuduino 1.44 (the version I used), I'm also hosting an [updated version of the library with compatibility with that version](https://github.com/zerkerX/MSF-XINPUT) locally.

To use this project, install the Arduino IDE and Teensyduino, then the MSF-XINPUT library, then build and install with the Arduino IDE and the XInput USB type. You can also use the included makefile to build easily outside the Arduino IDE, but you'll probably need to edit the IDE path to match your system. I also recommend making one change to the MSF-XINPUT library if using this joystick for both XInput and SNES/NES: reduce the **USB_TIMEOUT** so it is more responsive on the SNES side. I set mine to 1284, which is one tenth of the original.

The joystick I used this library for has six main action buttons on top, two start/select buttons on the front, and two pinball buttons on the sides for a total of 10. It also has three toggle switches (well, a push button and two switches) for changing controller behaviour and layout, and a separate button hardwired to the Teensy's **Program** line. 

Refer to `const int button_pins` in **ArcadeStick.hpp** for the exact pins used in my setup for each button position. Enum entries should also be removed for buttons you don't have to avoid confusion. This will require some changes to the XInput/SNES mappings, but that's cleaner than having unexpected behaviour.

Mapping between my generic buttons and XInput buttons is performed in **XInputMapper.hpp**, along with the alternate layouts for the toggles.

SNES protocol support and Mapping is provided by **SNESMapper.cpp**. This also provides three defines at the top of the file for the lines used for the latch, clock and data when emulating the SNES controller's shift register. Be sure to use pins that support interrupts for the clock and latch pins!

Since the Teensy LC uses 3.3 V logic, you will also need a line level converter to support the 5 V logic from the SNES. I used [this 4-channel converter from Adadruit](https://www.adafruit.com/product/757).
