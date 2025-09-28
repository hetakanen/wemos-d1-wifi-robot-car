#pragma once

#include "Led.h"
#include <Arduino.h>

class LedController
{
public:
    LedController()
    {
        led.setup();
        lastChangedTime = millis();
    }

    Led led;

    void toggle();
    void off();
    bool getShouldToggle(float distance);
private:    
    unsigned long lastChangedTime;
};
