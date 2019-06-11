#include <xinput.h>
#include "ArcadeStick.hpp"
#include "XInputMapper.hpp"
#include "SNESMapper.hpp"
#include "Profiler.hpp"

ArcadeStick stick;
XINPUT xinp(NO_LED);
XInputMapper xinp_map(stick);
Profiler prof(12);

void setup()
{
    SNESMapper::init();
}

void loop()
{
    stick.load();
    SNESMapper::load(stick);
    xinp_map.map_states(xinp);
    prof.start();
    xinp.sendXinput();
    xinp.receiveXinput();
    prof.end();
}
