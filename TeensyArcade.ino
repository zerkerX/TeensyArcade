#include <xinput.h>
#include "ArcadeStick.hpp"

ArcadeStick stick;

XINPUT xinp(NO_LED);

void setup()
{

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
