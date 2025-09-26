#include "Robot.h"
void Robot::stop()
{
    moveController.motors.stop();
    ledController.off();
}

void Robot::move(float distance)
{
    const unsigned long currentTime = millis();
    if (moveController.shouldBackup(moving, distance, minDistance))
    {
        moving = Direction::BACKWARD;
    }
    else if (moveController.shouldTurn(moving, distance, turnDistance))
    {
        action = Action::LOOKING;
        looking = Looking::LEFT;
    }
    else if (moveController.shouldMove(moving, distance, forwardDistance))
    {
        moving = Direction::FORWARD;
    }

    moveController.move(moving);
}

void Robot::look()
{
    switch (looking)
    {
    case Looking::LEFT:
        lookController.lookLeft([this]()
                                { looking = Looking::RIGHT; });
        break;
    case Looking::RIGHT:
        lookController.lookRight([this]()
                                 { looking = Looking::CENTER; });
        break;
    case Looking::CENTER:
        lookController.lookCenter([this](float dist, int rot)
                                  {
            moving = lookController.findDirection(dist, rot);
            action = Action::MOVING; });
        break;
    default:
        break;
    }
}
