//#include <stdbool.h>

enum joystick_buttons {
    STICK_LEFT = 0,
    STICK_RIGHT,
    STICK_UP,
    STICK_DOWN,
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

#define SNES_LATCH 22
#define SNES_CLOCK 23
#define SNES_DATA 21

int button_pins[NUM_BUTTONS] = 
{
    [STICK_LEFT] = 1,
    [STICK_RIGHT] = 0,
    [STICK_UP] = 3,
    [STICK_DOWN] = 2,
    [BUTTON_BLUE] = 16,
    [BUTTON_GREEN] = 15,
    [BUTTON_RED] = 17,
    [BUTTON_YELLOW] = 19,
    [BUTTON_TOP_LEFT] = 18,
    [BUTTON_TOP_RIGHT] = 20,
    [BUTTON_PB_LEFT] = 4,
    [BUTTON_PB_RIGHT] = 7,
    [BUTTON_FRONT_WHITE] = 5,
    [BUTTON_FRONT_BLACK] = 6,
    [TOGGLE_PUSH] = 9,
    [TOGGLE_SWITCH_1] = 8,
    [TOGGLE_SWITCH_2] = 10,
};

bool button_states[NUM_BUTTONS] = { [STICK_LEFT] = false };


void setup()
{
    int button;

    Serial.begin(19200);
    
    for (button = STICK_LEFT; button < NUM_BUTTONS; button++)
    {
        pinMode(button_pins[button], INPUT_PULLUP);
    } 

    pinMode(SNES_LATCH, INPUT_PULLUP);
    pinMode(SNES_CLOCK, INPUT_PULLUP);
    pinMode(SNES_DATA, OUTPUT);
}

void loop()
{
    int button;

    for (button = STICK_LEFT; button < NUM_BUTTONS; button++)
    {
        button_states[button] = !digitalRead(button_pins[button]);
    }
    
    Serial.printf("UDLR: %d%d%d%d, Top: %d%d%d%d%d%d, Side: %d%d, Front %d%d, Toggles: %d%d%d\r\n", 
        button_states[STICK_UP],
        button_states[STICK_DOWN],
        button_states[STICK_LEFT],
        button_states[STICK_RIGHT],

        button_states[BUTTON_BLUE],
        button_states[BUTTON_GREEN],
        button_states[BUTTON_RED],
        button_states[BUTTON_TOP_LEFT],
        button_states[BUTTON_YELLOW],
        button_states[BUTTON_TOP_RIGHT],

        button_states[BUTTON_PB_LEFT],
        button_states[BUTTON_PB_RIGHT],

        button_states[BUTTON_FRONT_WHITE],
        button_states[BUTTON_FRONT_BLACK],

        button_states[TOGGLE_PUSH],
        button_states[TOGGLE_SWITCH_1],
        button_states[TOGGLE_SWITCH_2]
        );

    delay(100);
}
