This repository is for the firmware for a Teensy LC-powered Arcade Stick, with the branch supporting newer libraries/Teensyduino releases. This project uses the [ArdunioXInput][xinput] library by Dave Madison for XInput protocol support and locally written code for mappings and SNES/NES support. This also requires some replacements to the board files from Teensyduino. The replacements are provided at the [ArduinoXInput_Teensy][xteensy] repo, also by Dave.

[xinput]: https://github.com/dmadison/ArduinoXInput
[xteensy]: https://github.com/dmadison/ArduinoXInput_Teensy

To use this project, install the Arduino IDE and Teensyduino, then the ArdunioXInput library, including the board replacement files. The library itself should be in the Arduino library search if you want to install that way. After setup, just then build and install with the Arduino IDE and the XInput USB type. You can also use the included makefile to build easily outside the Arduino IDE, but you'll probably need to edit the IDE path to match your system, and possibly some other tweaks. I also recommend making one change to the ArduinoXInput library if using this joystick for both XInput and SNES/NES: reduce the **USB_TIMEOUT** so it is more responsive on the SNES side. I set mine to 1284, which is one tenth of the original.

The joystick I used this library for has six main action buttons on top, two start/select buttons on the front, and two pinball buttons on the sides for a total of 10. It also has three toggle switches (well, a push button and two switches) for changing controller behaviour and layout, and a separate button hardwired to the Teensy's **Program** line. 

Refer to `const int button_pins` in **ArcadeStick.hpp** for the exact pins used in my setup for each button position. Enum entries should also be removed for buttons you don't have to avoid confusion. This will require some changes to the XInput/SNES mappings, but that's cleaner than having unexpected behaviour.

Mapping between my generic buttons and XInput buttons is performed in **XInputMapper.hpp**, along with the alternate layouts for the toggles.

SNES protocol support and Mapping is provided by **SNESMapper.cpp**. This also provides three defines at the top of the file for the lines used for the latch, clock and data when emulating the SNES controller's shift register. Be sure to use pins that support interrupts for the clock and latch pins!

Since the Teensy LC uses 3.3 V logic, you will also need a line level converter to support the 5 V logic from the SNES. I used [this 4-channel converter from Adadruit](https://www.adafruit.com/product/757).
