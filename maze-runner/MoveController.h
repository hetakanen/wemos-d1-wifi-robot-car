#pragma once
#include <Motors.h>
#include "enums.h"

class MoveController
{
public:
    MoveController()
    {
        motors.setup();
    }
    Motors motors{230, 200};
    bool shouldBackup(Direction moving, float distance, float minDistance);
    bool shouldMove(Direction moving, float distance, float turnDistance);
    bool shouldTurn(Direction moving, float distance, float turnDistance);
    void move(Direction moving);

private:
};