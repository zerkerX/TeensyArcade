#include <xinput.h>
#include "ArcadeStick.hpp"

#define SNES_LATCH 22
#define SNES_CLOCK 23
#define SNES_DATA 21

ArcadeStick stick;

XINPUT xinp(NO_LED);

void setup()
{
    pinMode(SNES_LATCH, INPUT_PULLUP);
    pinMode(SNES_CLOCK, INPUT_PULLUP);
    pinMode(SNES_DATA, OUTPUT);
}

void loop()
{
    stick.load();

    xinp.buttonArrayUpdate(stick.getButtonArray());
    uint8_t * dpad = stick.getDpadArray();
    xinp.dpadUpdate(dpad[ArcadeStick::XBOX_DPAD_UP], 
        dpad[ArcadeStick::XBOX_DPAD_DOWN],
        dpad[ArcadeStick::XBOX_DPAD_LEFT],
        dpad[ArcadeStick::XBOX_DPAD_RIGHT] );
    xinp.triggerUpdate(
        stick.getLeftTrigger(),
        stick.getRightTrigger() );
    xinp.stickUpdate(STICK_LEFT, stick.getStickX(), stick.getStickY());

    xinp.sendXinput();
    xinp.receiveXinput();
}
