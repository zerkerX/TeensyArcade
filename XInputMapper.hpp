#ifndef XINPUT_MAPPER_HPP
#define XINPUT_MAPPER_HPP

#include "ArcadeStick.hpp"
#include <xinput.h>

class XInputMapper
{
  public:
    // To align with MSF XINPUT ordering
    enum xbox_mapped_button_t {
        XBOX_A = 0,
        XBOX_B,
        XBOX_X,
        XBOX_Y,
        XBOX_LB,
        XBOX_RB,
        XBOX_L3,
        XBOX_R3,
        XBOX_START,
        XBOX_BACK,
        XBOX_LOGO,
        NUM_XBOX_BUTTONS
    };

    XInputMapper(const ArcadeStick & stick) : stick(stick) {}
    
    
    void map_states(XINPUT & xinp)
    {
        // Selected mappings
        ArcadeStick::joystick_button_t lb, rb, lt, rt;

        // Xinput results:
        uint8_t xbox_button_array[NUM_XBOX_BUTTONS] = {0};
        uint8_t pad_up = 0, pad_down = 0, 
            pad_left = 0, pad_right = 0;
        uint8_t left_trigger = 0;
        uint8_t right_trigger = 0;
        int16_t xaxis = 0;
        int16_t yaxis = 0;

        // Select mapping for Bumpers vs Triggers
        if (stick.button(ArcadeStick::TOGGLE_SWITCH_1))
        {
            lb = ArcadeStick::BUTTON_PB_LEFT;
            rb = ArcadeStick::BUTTON_PB_RIGHT;
            lt = ArcadeStick::BUTTON_TOP_LEFT;
            rt = ArcadeStick::BUTTON_TOP_RIGHT;
        }
        else
        {
            lb = ArcadeStick::BUTTON_TOP_LEFT;
            rb = ArcadeStick::BUTTON_TOP_RIGHT;
            lt = ArcadeStick::BUTTON_PB_LEFT;
            rt = ArcadeStick::BUTTON_PB_RIGHT;
        }
        
        // Select standard vs fighting game layout
        if (!stick.button(ArcadeStick::TOGGLE_SWITCH_2))
        {
            // Standard layout
            xbox_button_array[XBOX_A] = stick.button(ArcadeStick::BUTTON_GREEN);
            xbox_button_array[XBOX_B] = stick.button(ArcadeStick::BUTTON_RED);
            xbox_button_array[XBOX_X] = stick.button(ArcadeStick::BUTTON_BLUE);
        }
        else
        {
            // Fighting game layout
            xbox_button_array[XBOX_X] = stick.button(ArcadeStick::BUTTON_TOP_LEFT);
            xbox_button_array[XBOX_A] = stick.button(ArcadeStick::BUTTON_BLUE);
            xbox_button_array[XBOX_B] = stick.button(ArcadeStick::BUTTON_GREEN);

            // Re-select top button mappings (pinball buttons don't change)
            if (stick.button(ArcadeStick::TOGGLE_SWITCH_1))
            {
                lt = ArcadeStick::BUTTON_TOP_RIGHT;
                rt = ArcadeStick::BUTTON_RED;
            }
            else
            {
                lb = ArcadeStick::BUTTON_TOP_RIGHT;
                rb = ArcadeStick::BUTTON_RED;
            }
        }

        // Y Button is always the same
        xbox_button_array[XBOX_Y] = stick.button(ArcadeStick::BUTTON_YELLOW);

        xbox_button_array[XBOX_START] = stick.button(ArcadeStick::BUTTON_FRONT_BLACK);
        xbox_button_array[XBOX_BACK] = stick.button(ArcadeStick::BUTTON_FRONT_WHITE);
        
        /* No dedicated logo button (not needed on Windows), but if using adaptor
         * for PS3/PS4, both front buttons will have that effect.
         * Hopefully there's no need to explicitly disable the start/back buttons
         * in this scenario */
        xbox_button_array[XBOX_LOGO] = stick.button(ArcadeStick::BUTTON_FRONT_BLACK) 
            && stick.button(ArcadeStick::BUTTON_FRONT_WHITE);
        
        xbox_button_array[XBOX_LB] = stick.button(lb);
        xbox_button_array[XBOX_RB] = stick.button(rb);
        
        if (stick.button(lt))
            left_trigger = 255;
        else
            left_trigger = 0;
        
        if (stick.button(rt))
            right_trigger = 255;
        else
            right_trigger = 0;
        
        // Select between DPAD or Stick control
        if (stick.button(ArcadeStick::TOGGLE_PUSH))
        {
            // DPAD mapped to Stick
            pad_up = stick.button(ArcadeStick::JSTICK_UP);
            pad_down = stick.button(ArcadeStick::JSTICK_DOWN);
            pad_left = stick.button(ArcadeStick::JSTICK_LEFT);
            pad_right = stick.button(ArcadeStick::JSTICK_RIGHT);
            
            xaxis = 0;
            yaxis = 0;
        }
        else
        {
            // Left Analog stick mapped to Stick
            if (stick.button(ArcadeStick::JSTICK_LEFT))
                xaxis = INT16_MIN;
            else if (stick.button(ArcadeStick::JSTICK_RIGHT))
                xaxis = INT16_MAX;
            else
                xaxis = 0;

            if (stick.button(ArcadeStick::JSTICK_UP))
                yaxis = INT16_MAX;
            else if (stick.button(ArcadeStick::JSTICK_DOWN))
                yaxis = INT16_MIN;
            else
                yaxis = 0;
                
            // DPAD zero by default. Just leave that way.
        }
        
        // Assign to the xinput device
        xinp.buttonArrayUpdate(xbox_button_array);
        xinp.dpadUpdate(pad_up, pad_down, pad_left, pad_right);
        xinp.triggerUpdate(left_trigger, right_trigger);
        xinp.stickUpdate(STICK_LEFT, xaxis, yaxis);
    }
    
   
  private:

    const ArcadeStick & stick;
};

#endif
