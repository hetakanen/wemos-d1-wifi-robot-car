#include "LedController.h"

void LedController::toggle()
{
    led.toggle();
    lastChangedTime = millis();
}

bool LedController::getShouldToggle(float distance)
{
    const unsigned long currentTime = millis();
    return currentTime - lastChangedTime >= distance * 10;
}

void LedController::off()
{
    led.off();
}
