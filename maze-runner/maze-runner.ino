#include "Robot.h"
#include "LookController.h"

Robot robot;
LookController lookController(robot);

const unsigned long loopDelay = 200;
unsigned long lastChangedTime;

void setup()
{
  lastChangedTime = millis();
}

void loop()
{
  const bool isButtonPressed = robot.pauseButton.isPressed();
  if (isButtonPressed)
  {
    robot.isRunning = !robot.isRunning;
  }

  if (robot.isRunning)
  {
    const float distance = robot.sensor.readDistance();
    handleLed(distance);

    if (robot.action == Action::LOOKING)
    {
      robot.motors.stop();
      lookController.lookAround(distance);
    }
    else
    {
      if (robot.moving == Direction::FORWARD || robot.moving == Direction::BACKWARD)
      {
        if (distance < robot.minDistance)
        {
          robot.moving = Direction::BACKWARD;
        }
        else if (distance < robot.turnDistance)
        {
          robot.action = Action::LOOKING;
          robot.looking = Looking::LEFT;
        }
        else
        {
          robot.moving = Direction::FORWARD;
        }
      }

      switch (robot.moving)
      {
      case Direction::FORWARD:
        robot.motors.moveForward();
        break;
      case Direction::BACKWARD:
        robot.motors.moveBackward();
        break;
      case Direction::TURN_LEFT:
        robot.motors.moveLeft();
        if (distance > robot.turnDistance)
        {
          robot.moving = Direction::FORWARD;
        }
        break;
      case Direction::TURN_RIGHT:
        robot.motors.moveRight();
        if (distance > robot.turnDistance)
        {
          robot.moving = Direction::FORWARD;
        }
        break;
      default:
        break;
      }
    }
  }
  else
  {
    robot.motors.stop();
    robot.led.off();
  }

  delay(loopDelay);
}

void handleLed(float distance)
{
  const unsigned long currentTime = millis();
  const bool shouldToggleLed = currentTime - lastChangedTime >= distance * 10;

  if (shouldToggleLed)
  {
    robot.led.toggle();
    lastChangedTime = millis();
  }
}
