#include "LookController.h"

void LookController::lookLeft(AfterLookingCallback callback)
{
    rotateTo(sensor.LEFT, [this, callback](float d)
             {
        longestDistance.reset();
        longestDistance.updateIfLonger(sensor.LEFT, d);
        callback(); });
}

void LookController::lookRight(AfterLookingCallback callback)
{
    rotateTo(sensor.RIGHT, [this, callback](float d)
             {

        longestDistance.updateIfLonger(sensor.RIGHT, d);
        callback(); });
}

void LookController::lookCenter(AfterLookingWithResultCallback callback)
{
    rotateTo(sensor.CENTER, [this, callback](float d)
             { callback(longestDistance.distance, longestDistance.rotation); });
}

Direction LookController::findDirection(const float distance, const int rotation) const
{
    if (distance <= minDistance)
    {
        return Direction::BACKWARD;
    }
    if (rotation == sensor.LEFT)
    {
        return Direction::TURN_LEFT;
    }
    if (rotation == sensor.RIGHT)
    {
        return Direction::TURN_RIGHT;
    }
    return Direction::BACKWARD;
}

void LookController::rotateTo(int direction, CallbackType callback)
{
    if (sensor.getRotation() != direction)
    {
        sensor.lookAt(direction);
    }
    else
    {
        sensor.addDelay();
        const float d = sensor.readDistance();
        callback(d);
    }
}
