#include <XInput.h>
#include "ArcadeStick.hpp"
#include "XInputMapper.hpp"
#include "SNESMapper.hpp"

ArcadeStick stick;
XInputMapper xinp_map(stick);

void setup()
{
    SNESMapper::init();
    XInput.setAutoSend(false);
    XInput.begin();
}

void loop()
{
    stick.load();
    SNESMapper::load(stick);
    xinp_map.map_states();
    XInput.send();
}
