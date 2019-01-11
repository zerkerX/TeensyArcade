#ifndef ARCADE_STICK_HPP
#define ARCADE_STICK_HPP

#include <Arduino.h>

class ArcadeStick
{
  public:
    enum joystick_button_t {
        JSTICK_LEFT = 0,
        JSTICK_RIGHT,
        JSTICK_UP,
        JSTICK_DOWN,
        BUTTON_BLUE,
        BUTTON_GREEN,
        BUTTON_RED,
        BUTTON_YELLOW,
        BUTTON_TOP_LEFT,
        BUTTON_TOP_RIGHT,
        BUTTON_PB_LEFT,
        BUTTON_PB_RIGHT,
        BUTTON_FRONT_WHITE,
        BUTTON_FRONT_BLACK,
        TOGGLE_PUSH,
        TOGGLE_SWITCH_1,
        TOGGLE_SWITCH_2,
        NUM_BUTTONS
    };
    
    ArcadeStick()
    {
        for (int button = JSTICK_LEFT; button < NUM_BUTTONS; button++)
        {
            pinMode(button_pins[button], INPUT_PULLUP);
        } 
    }
    
    
    void load()
    {
        for (int button = JSTICK_LEFT; button < NUM_BUTTONS; button++)
        {
            button_states[button] = !digitalRead(button_pins[button]);
        }
    }

    
    inline bool button(joystick_button_t button) const
    {
        return button_states[button];
    }

   
  private:

    const int button_pins[NUM_BUTTONS] = 
    {
        1, // STICK_LEFT
        0, // STICK_RIGHT
        3, // STICK_UP
        2, // STICK_DOWN
        16, // BUTTON_BLUE
        15, // BUTTON_GREEN
        17, // BUTTON_RED
        19, // BUTTON_YELLOW
        18, // BUTTON_TOP_LEFT
        20, // BUTTON_TOP_RIGHT
        4, // BUTTON_PB_LEFT
        7, // BUTTON_PB_RIGHT
        5, // BUTTON_FRONT_WHITE
        6, // BUTTON_FRONT_BLACK
        9, // TOGGLE_PUSH
        8, // TOGGLE_SWITCH_1
        10, // TOGGLE_SWITCH_2
    };

    bool button_states[NUM_BUTTONS] = { false };
};

#endif
