#include <xinput.h>
#include "ArcadeStick.hpp"
#include "XInputMapper.hpp"

#define SNES_LATCH 22
#define SNES_CLOCK 21
#define SNES_DATA 23

ArcadeStick stick;
XINPUT xinp(NO_LED);
XInputMapper xinp_map(stick);

void setup()
{
    pinMode(SNES_LATCH, INPUT_PULLUP);
    pinMode(SNES_CLOCK, INPUT_PULLUP);
    pinMode(SNES_DATA, OUTPUT);
}

void loop()
{
    stick.load();
    xinp_map.map_states(xinp);
    xinp.sendXinput();
    xinp.receiveXinput();
}
