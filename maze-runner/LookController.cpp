#include "LookController.h"

void LookController::lookAround(float distance)
{
    switch (robot.looking)
    {
    case Looking::LEFT:
        handleLook(robot.sensor.LEFT, Looking::RIGHT, distance);
        break;
    case Looking::RIGHT:
        handleLook(robot.sensor.RIGHT, Looking::CENTER, distance);
        break;
    case Looking::CENTER:
        lookAt(robot.sensor.CENTER, [this](float d)
               {
            robot.moving = findDirection(longestDistance);
            robot.action = Action::MOVING;
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
        return Direction::TURN_LEFT;
    }
    if (dist.rotation == robot.sensor.RIGHT)
    {
        return Direction::TURN_RIGHT;
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