#pragma once

#include <Motors.h>
#include <PauseButton.h>

#include "LookController.h"
#include "LedController.h"
#include "MoveController.h"
#include "enums.h"

#include <Arduino.h>

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
        Serial.begin(9600);
        pauseButton.setup();
    }

    void stop();
    void look();
    void move(float distance);

    const float forwardDistance = 30.0;
    const float turnDistance = 20.0;
    const float minDistance = 10.0;
private:
    unsigned long timeStartedMovingBack;
};