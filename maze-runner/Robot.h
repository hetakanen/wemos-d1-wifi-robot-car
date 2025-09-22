#pragma once

#include <Motors.h>
#include <PauseButton.h>

#include "LookController.h"
#include "LedController.h"
#include "MoveController.h"
#include "enums.h"

class Robot
{
public:
    MoveController moveController;
    PauseButton pauseButton;

    LedController ledController;
    LookController lookController{minDistance};

    Action action;
    
    Looking looking;
    Direction moving;
    bool isRunning;

    Robot() : action(Action::MOVING), looking(Looking::LEFT), moving(Direction::FORWARD), isRunning(false)
    {
        pauseButton.setup();
    }

    void stop();
    void look(float distance);
    void move(float distance);

    const float turnDistance = 20.0;
    const float minDistance = 10.0;
};