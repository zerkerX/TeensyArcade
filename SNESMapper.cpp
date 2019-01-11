#include "SNESMapper.hpp"
#include <Arduino.h>
#include <cstdint>

/* Using bare variables instead of a class because we'd have to do 
 * everything statically anyways to define our ISRs. Easier to just
 * go with a C-style design instead.*/
#define SNES_LATCH 22
#define SNES_CLOCK 21
#define SNES_DATA 23

namespace SNESMapper
{

union snespad_t
{
    uint16_t data;
    
    struct
    {
        // Clock Data to the right/LSB, but board is Little Endian. 
        // Top entries are therefore clocked first
        uint16_t   button_B: 1;
        uint16_t   button_Y: 1;
        uint16_t   button_Select: 1;
        uint16_t   button_Start: 1;
        uint16_t   dpad_up: 1;
        uint16_t   dpad_down: 1;
        uint16_t   dpad_left: 1;
        uint16_t   dpad_right: 1;
        uint16_t   button_A: 1;
        uint16_t   button_X: 1;
        uint16_t   button_L: 1;
        uint16_t   button_R: 1;
        uint16_t   padding: 4;
    };
};

volatile uint16_t shiftreg = 0xFFFF;
volatile snespad_t snesdata = { 0xFFFF };

/** ISR when the SNES LATCH line is set to HIGH. Stores the buttons into
 * the shift register and prepares the first value on the data line.*/
void latchvalues()
{
    shiftreg = snesdata.data;
    digitalWrite(SNES_DATA, shiftreg & 1);
    shiftreg = shiftreg >> 1;
}

/** ISR for the SNES CLOCK pulse. Shifts the next value onto the data line.
 * Note this is technically the same clock pulse as the SNES samples at,
 * but with ISR overhead, we will always be after the sample and thus preparing
 * the NEXT value.*/
void shiftvalues()
{
    digitalWrite(SNES_DATA, shiftreg & 1);
    shiftreg = shiftreg >> 1;
}


void init(void)
{
    pinMode(SNES_LATCH, INPUT_PULLUP);
    pinMode(SNES_CLOCK, INPUT_PULLUP);
    pinMode(SNES_DATA, OUTPUT);
    
    attachInterrupt(digitalPinToInterrupt(SNES_CLOCK), shiftvalues, FALLING);
    attachInterrupt(digitalPinToInterrupt(SNES_LATCH), latchvalues, RISING);
}


void load(const ArcadeStick & stick)
{
    /* The SNES data should be inverted logic (high = released), so
     * reverse the state of the joystick itself */
     
    /* NOTE: We intentionally don't clear the existing state, merely overwrite
     * it. If we get interrupted by the ISR, we don't want buttons toggling */
    snesdata.dpad_up = !stick.button(ArcadeStick::JSTICK_UP);
    snesdata.dpad_down = !stick.button(ArcadeStick::JSTICK_DOWN);
    snesdata.dpad_left = !stick.button(ArcadeStick::JSTICK_LEFT);
    snesdata.dpad_right = !stick.button(ArcadeStick::JSTICK_RIGHT);
    
    snesdata.button_Y = !stick.button(ArcadeStick::BUTTON_BLUE);
    snesdata.button_B = !stick.button(ArcadeStick::BUTTON_GREEN);
    snesdata.button_A = !stick.button(ArcadeStick::BUTTON_RED);
    snesdata.button_X = !stick.button(ArcadeStick::BUTTON_YELLOW);
    snesdata.button_L = !stick.button(ArcadeStick::BUTTON_TOP_LEFT);
    snesdata.button_R = !stick.button(ArcadeStick::BUTTON_TOP_RIGHT);
    snesdata.button_Select = !stick.button(ArcadeStick::BUTTON_FRONT_WHITE);
    snesdata.button_Start = !stick.button(ArcadeStick::BUTTON_FRONT_BLACK);
}


}
