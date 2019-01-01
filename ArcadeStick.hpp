#include <cstring>

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
    
    enum xbox_dpad_t {
        XBOX_DPAD_UP = 0,
        XBOX_DPAD_DOWN,
        XBOX_DPAD_LEFT,
        XBOX_DPAD_RIGHT,
        NUM_XBOX_DPAD
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
        // Selected mappings
        joystick_button_t lb;
        joystick_button_t rb;
        joystick_button_t lt;
        joystick_button_t rt;
        
        for (int button = JSTICK_LEFT; button < NUM_BUTTONS; button++)
        {
            button_states[button] = !digitalRead(button_pins[button]);
        }
        
        // Populate mapped results:
        memset(xbox_button_array, 0, NUM_XBOX_BUTTONS);
        memset(xbox_dpad, 0, NUM_XBOX_DPAD);
        
        // Select mapping for Bumpers vs Triggers
        if (button_states[TOGGLE_SWITCH_1])
        {
            lb = BUTTON_PB_LEFT;
            rb = BUTTON_PB_RIGHT;
            lt = BUTTON_TOP_LEFT;
            rt = BUTTON_TOP_RIGHT;
        }
        else
        {
            lb = BUTTON_TOP_LEFT;
            rb = BUTTON_TOP_RIGHT;
            lt = BUTTON_PB_LEFT;
            rt = BUTTON_PB_RIGHT;
        }
        
        // Select standard vs fighting game layout
        if (button_states[TOGGLE_SWITCH_2])
        {
            // Standard layout
            xbox_button_array[XBOX_A] = button_states[BUTTON_GREEN];
            xbox_button_array[XBOX_B] = button_states[BUTTON_RED];
            xbox_button_array[XBOX_X] = button_states[BUTTON_BLUE];
        }
        else
        {
            // Fighting game layout
            xbox_button_array[XBOX_X] = button_states[BUTTON_TOP_LEFT];
            xbox_button_array[XBOX_A] = button_states[BUTTON_BLUE];
            xbox_button_array[XBOX_B] = button_states[BUTTON_GREEN];

            // Re-select top button mappings (pinball buttons don't change)
            if (button_states[TOGGLE_SWITCH_1])
            {
                lt = BUTTON_TOP_RIGHT;
                rt = BUTTON_RED;
            }
            else
            {
                lb = BUTTON_TOP_RIGHT;
                rb = BUTTON_RED;
            }
        }

        // Y Button is always the same
        xbox_button_array[XBOX_Y] = button_states[BUTTON_YELLOW];

        xbox_button_array[XBOX_START] = button_states[BUTTON_FRONT_BLACK];
        xbox_button_array[XBOX_BACK] = button_states[BUTTON_FRONT_WHITE];
        
        xbox_button_array[XBOX_LB] = button_states[lb];
        xbox_button_array[XBOX_RB] = button_states[rb];
        
        if (button_states[lt])
            left_trigger = 255;
        else
            left_trigger = 0;
        
        if (button_states[rt])
            right_trigger = 255;
        else
            right_trigger = 0;
        
        // Select between DPAD or Stick control
        if (button_states[TOGGLE_PUSH])
        {
            // DPAD mapped to Stick
            xbox_dpad[XBOX_DPAD_UP] = button_states[JSTICK_UP];
            xbox_dpad[XBOX_DPAD_DOWN] = button_states[JSTICK_DOWN];
            xbox_dpad[XBOX_DPAD_LEFT] = button_states[JSTICK_LEFT];
            xbox_dpad[XBOX_DPAD_RIGHT] = button_states[JSTICK_RIGHT];
            
            xaxis = 0;
            yaxis = 0;
        }
        else
        {
            // Left Analog stick mapped to Stick
            if (button_states[JSTICK_LEFT])
                xaxis = INT16_MIN;
            else if (button_states[JSTICK_RIGHT])
                xaxis = INT16_MAX;
            else
                xaxis = 0;

            if (button_states[JSTICK_UP])
                yaxis = INT16_MAX;
            else if (button_states[JSTICK_DOWN])
                yaxis = INT16_MIN;
            else
                yaxis = 0;
                
            // DPAD already zeroed above. Just leave that way.
        }
    }
    
    
    inline bool button(joystick_button_t button)
    {
        return button_states[button];
    }
    
    inline uint8_t * getButtonArray()
    {
        return xbox_button_array;
    }

    inline uint8_t * getDpadArray()
    {
        return xbox_dpad;
    }

    inline uint8_t getLeftTrigger()
    {
        return left_trigger;
    }

    inline uint8_t getRightTrigger()
    {
        return right_trigger;
    }

    inline int16_t getStickX()
    {
        return xaxis;
    }

    inline int16_t getStickY()
    {
        return yaxis;
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
    
    uint8_t xbox_button_array[NUM_XBOX_BUTTONS];
    uint8_t xbox_dpad[NUM_XBOX_DPAD];
    uint8_t left_trigger;
    uint8_t right_trigger;
    int16_t xaxis;
    int16_t yaxis;
};
