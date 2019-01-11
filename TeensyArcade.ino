#include <xinput.h>
#include "ArcadeStick.hpp"
#include "XInputMapper.hpp"
#include "SNESMapper.hpp"

ArcadeStick stick;
XINPUT xinp(NO_LED);
XInputMapper xinp_map(stick);

void setup()
{
    SNESMapper::init();
}

void loop()
{
    stick.load();
    SNESMapper::load(stick);
    xinp_map.map_states(xinp);
    xinp.sendXinput();
    xinp.receiveXinput();
}
