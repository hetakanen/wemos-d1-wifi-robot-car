#include "LookController.h"

void LookController::lookLeft(float distance, AfterLookingCallback callback)
{
    rotateTo(sensor.LEFT, [this, callback](float d)
             {

        longestDistance.updateIfLonger(sensor.LEFT, d);
        callback(); }, distance);
}

void LookController::lookRight(float distance, AfterLookingCallback callback)
{
    rotateTo(sensor.RIGHT, [this, callback](float d)
             {

        longestDistance.updateIfLonger(sensor.RIGHT, d);

        callback(); }, distance);
}

void LookController::lookCenter(float distance, AfterLookingWithResultCallback callback)
{
    rotateTo(sensor.CENTER, [this, callback](float d)
             {
                callback(longestDistance.distance, longestDistance.rotation);
                longestDistance.reset(); }, distance);
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

void LookController::rotateTo(int direction, CallbackType callback, float distance)
{
    if (sensor.getRotation() != direction)
    {
        sensor.lookAt(direction);
    }
    else
    {
        callback(distance);
    }
}
