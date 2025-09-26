#include "MoveController.h"

bool MoveController::shouldTurn(Direction moving, float distance, float turnDistance)
{
    if (moving == Direction::FORWARD)
    {
        return distance <= turnDistance;
    }
    else if(moving == Direction::BACKWARD) {
        return distance >= turnDistance;
    }
    return false;
}

bool MoveController::shouldBackup(Direction moving, float distance, float minDistance)
{
    return distance <= minDistance;
}

bool MoveController::shouldMove(Direction moving, float distance, float forwardDistance)
{
    if (moving == Direction::TURN_LEFT || moving == Direction::TURN_RIGHT)
    {
        return distance >= forwardDistance;
    }
    return false;
}

void MoveController::move(Direction moving)
{
    switch (moving)
    {
    case Direction::FORWARD:
        motors.moveForward();
        break;
    case Direction::BACKWARD:
        motors.moveBackward();
        break;
    case Direction::TURN_LEFT:
        motors.moveLeft();
        break;
    case Direction::TURN_RIGHT:
        motors.moveRight();
        break;
    default:
        break;
    }
}