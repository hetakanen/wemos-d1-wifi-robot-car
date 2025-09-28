#pragma once

#include <UltrasonicSensor.h>
#include "Distance.h"
#include "enums.h"
#include <functional>

class LookController
{
public:
    LookController(const float &minDistance) : minDistance(minDistance)
    {
        sensor.setup();
    }

    using CallbackType = std::function<void(float)>;
    using AfterLookingCallback = std::function<void()>;
    using AfterLookingWithResultCallback = std::function<void(float, int)>;

    Direction findDirection(const float distance, const int rotation) const;
    void lookLeft(AfterLookingCallback callback);
    void lookRight(AfterLookingCallback callback);
    void lookCenter(AfterLookingWithResultCallback callback);
    void rotateTo(int direction, CallbackType callback);

    UltrasonicSensor sensor;

private:
    const float minDistance;
    Distance longestDistance;
};