#include "ArcadeStick.hpp"

#define SNES_LATCH 22
#define SNES_CLOCK 23
#define SNES_DATA 21

ArcadeStick stick;

void setup()
{
    Joystick.useManualSend(true);

    pinMode(SNES_LATCH, INPUT_PULLUP);
    pinMode(SNES_CLOCK, INPUT_PULLUP);
    pinMode(SNES_DATA, OUTPUT);
}

void loop()
{
    stick.load();
    Joystick.button(1, stick.button(ArcadeStick::BUTTON_BLUE));
    Joystick.button(2, stick.button(ArcadeStick::BUTTON_GREEN));
    Joystick.button(3, stick.button(ArcadeStick::BUTTON_RED));

    Joystick.send_now();

    delay(100);
}
