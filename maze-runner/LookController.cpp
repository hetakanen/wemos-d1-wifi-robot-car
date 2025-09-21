#include "LookController.h"

void LookController::lookAround(float distance)
{
    switch (robot.looking)
    {
    case Looking::LOOK_LEFT:
        handleLook(robot.sensor.LEFT, Looking::LOOK_RIGHT, distance);
        break;
    case Looking::LOOK_RIGHT:
        handleLook(robot.sensor.RIGHT, Looking::LOOK_CENTER, distance);
        break;
    case Looking::LOOK_CENTER:
        lookAt(robot.sensor.CENTER, [this](float d)
               {
            robot.direction = findDirection(longestDistance);
            longestDistance.reset(); }, distance);
        break;
    default:
        break;
    }
}

void LookController::handleLook(int sensorDir, Looking nextLook, float distance)
{
    lookAt(sensorDir, [this, sensorDir, nextLook](float d)
           {
        longestDistance.updateIfLonger(sensorDir, d);
        robot.looking = nextLook; }, distance);
}

Direction LookController::findDirection(const Distance &dist) const
{
    if (dist.distance <= robot.minDistance)
    {
        return Direction::BACKWARD;
    }
    if (dist.rotation == robot.sensor.LEFT)
    {
        return Direction::LEFT;
    }
    if (dist.rotation == robot.sensor.RIGHT)
    {
        return Direction::RIGHT;
    }
    return Direction::BACKWARD;
}

void LookController::lookAt(int direction, CallbackType callback, float distance)
{
    if (robot.sensor.getRotation() != direction)
    {
        robot.sensor.lookAt(direction);
    }
    else
    {
        callback(distance);
    }
}