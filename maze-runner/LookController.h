#pragma once
#include "Distance.h"
#include "Robot.h"
#include "Arduino.h"
#include <functional>

class LookController
{
public:
    LookController(Robot &robot) : robot(robot)
    {
    }
    void lookAround(float distance);

private:
    Robot &robot;
    using CallbackType = std::function<void(float)>;
    Distance longestDistance;
    void handleLook(int sensorDir, Looking nextLook, float distance);
    Direction findDirection(const Distance &dist) const;
    void lookAt(int direction, CallbackType callback, float distance);
};