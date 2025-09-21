#include "distance.h"

void Distance::reset()
{
    rotation = -1;
    distance = -1;
}

void Distance::updateIfLonger(int rotation, float distance)
{
    if (distance > this->distance)
    {
        this->rotation = rotation;
        this->distance = distance;
    }
}