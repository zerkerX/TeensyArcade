#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <Arduino.h>

class Profiler
{
  public:
    Profiler(int pin) : profile_pin(pin)
    {
        pinMode(profile_pin, OUTPUT);
    }
    
    void start()
    {
        digitalWrite(profile_pin, HIGH);
    }
    
    void end()
    {
        digitalWrite(profile_pin, LOW);
    }
   
  private:

    int profile_pin;
};

#endif
