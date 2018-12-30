int pins[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    15, 16, 17, 18, 19, 20, 21, 22, 23
};

#define NUMPINS (sizeof(pins) / sizeof(int))



void setup()
{
    size_t i;
    Serial.begin(19200);
    
    for (i = 0; i < NUMPINS; i++)
    {
        pinMode(pins[i], INPUT_PULLUP);
    } 
}

void loop()
{
    size_t i;

    for (i = 0; i < NUMPINS; i++)
    {
        Serial.printf("%d: %d; ", pins[i], digitalRead(pins[i]));
    }
    Serial.println("");

    delay(100);
}
