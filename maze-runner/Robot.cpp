#include "Robot.h"

void Robot::stop()
{
    moveController.motors.stop();
    ledController.off();
}

void Robot::move(float distance)
{
    if (moveController.shouldBackup(moving, distance, minDistance))
    {
        moving = Direction::BACKWARD;
    }
    else if (moveController.shouldTurn(moving, distance, turnDistance))
    {
        action = Action::LOOKING;
        looking = Looking::LEFT;
    }
    else if (moveController.shouldMove(moving, distance, turnDistance))
    {
        moving = Direction::FORWARD;
    }

    moveController.move(moving);
}

void Robot::look(float distance)
{
    switch (looking)
    {
    case Looking::LEFT:
        lookController.lookLeft(distance, [this]()
                                { looking = Looking::RIGHT; });
        break;
    case Looking::RIGHT:
        lookController.lookRight(distance, [this]()
                                 { looking = Looking::CENTER; });
        break;
    case Looking::CENTER:
        lookController.lookCenter(distance, [this](float dist, int rot)
                                  {
            moving = lookController.findDirection(dist, rot);
            action = Action::MOVING; });
        break;
    default:
        break;
    }
}
