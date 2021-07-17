#ifndef XINPUT_MAPPER_HPP
#define XINPUT_MAPPER_HPP

#include "ArcadeStick.hpp"
#include <XInput.h>

class XInputMapper
{
  public:
    XInputMapper(const ArcadeStick & stick) : stick(stick) {}
    
    void map_states()
    {
        // Selected mappings
        ArcadeStick::joystick_button_t lb, rb, lt, rt;

        // Xinput results:
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
            XInput.setButton(BUTTON_A, stick.button(ArcadeStick::BUTTON_GREEN));
            XInput.setButton(BUTTON_B, stick.button(ArcadeStick::BUTTON_RED));
            XInput.setButton(BUTTON_X, stick.button(ArcadeStick::BUTTON_BLUE));
        }
        else
        {
            // Fighting game layout
            XInput.setButton(BUTTON_X, stick.button(ArcadeStick::BUTTON_TOP_LEFT));
            XInput.setButton(BUTTON_A, stick.button(ArcadeStick::BUTTON_BLUE));
            XInput.setButton(BUTTON_B, stick.button(ArcadeStick::BUTTON_GREEN));

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
        XInput.setButton(BUTTON_Y, stick.button(ArcadeStick::BUTTON_YELLOW));

        XInput.setButton(BUTTON_START, stick.button(ArcadeStick::BUTTON_FRONT_BLACK));
        XInput.setButton(BUTTON_BACK, stick.button(ArcadeStick::BUTTON_FRONT_WHITE));
        XInput.setButton(BUTTON_LOGO, stick.button(ArcadeStick::BUTTON_FRONT_CLEAR));
        
        XInput.setButton(BUTTON_LB, stick.button(lb));
        XInput.setButton(BUTTON_RB, stick.button(rb));
        
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
        XInput.setDpad(pad_up, pad_down, pad_left, pad_right);
        XInput.setTrigger(TRIGGER_LEFT,  left_trigger);
        XInput.setTrigger(TRIGGER_RIGHT, right_trigger);
        XInput.setJoystick(JOY_LEFT, xaxis, yaxis);
    }
    
   
  private:

    const ArcadeStick & stick;
};

#endif
