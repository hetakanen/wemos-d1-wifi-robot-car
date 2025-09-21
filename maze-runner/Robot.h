#pragma once

#include <UltrasonicSensor.h>
#include <Motors.h>
#include <PauseButton.h>
#include <Led.h>

enum class Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    LOOKING
};

enum class Looking
{
    LOOK_LEFT,
    LOOK_CENTER,
    LOOK_RIGHT
};

class Robot
{
public:
    UltrasonicSensor sensor;
    Motors motors;
    PauseButton pauseButton;
    Led led;

    Direction direction;
    Looking looking;
    bool isRunning;

    Robot() : direction(Direction::FORWARD), looking(Looking::LOOK_CENTER), isRunning(false)
    {
        sensor.setup();
        motors.setup();
        pauseButton.setup();
        led.setup();
    }

    const float turnDistance = 20.0;
    const float minDistance = 10.0;
};