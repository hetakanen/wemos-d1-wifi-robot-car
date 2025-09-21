#pragma once

#include <UltrasonicSensor.h>
#include <Motors.h>
#include <PauseButton.h>
#include <Led.h>

enum class Action
{
    MOVING,
    LOOKING
};

enum class Direction
{
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT
};

enum class Looking
{
    LEFT,
    RIGHT,
    CENTER
};

class Robot
{
public:
    UltrasonicSensor sensor;
    Motors motors;
    PauseButton pauseButton;
    Led led;

    Action action;
    Direction moving;
    Looking looking;
    bool isRunning;

    Robot() : action(Action::MOVING), moving(Direction::FORWARD), looking(Looking::CENTER), isRunning(false)
    {
        sensor.setup();
        motors.setup();
        pauseButton.setup();
        led.setup();
    }

    const float turnDistance = 20.0;
    const float minDistance = 10.0;
};