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

    if (robot.direction == Direction::FORWARD || robot.direction == Direction::BACKWARD)
    {
      if (distance < robot.minDistance)
      {
        robot.direction = Direction::BACKWARD;
      }
      else if (distance < robot.turnDistance)
      {
        robot.direction = Direction::LOOKING;
        robot.looking = Looking::LOOK_LEFT;
      }
      else
      {
        robot.direction = Direction::FORWARD;
      }
    }

    switch (robot.direction)
    {
    case Direction::FORWARD:
      robot.motors.moveForward();
      break;
    case Direction::BACKWARD:
      robot.motors.moveBackward();
      break;
    case Direction::LEFT:
      robot.motors.moveLeft();
      if (distance > robot.turnDistance)
      {
        robot.direction = Direction::FORWARD;
      }
      break;
    case Direction::RIGHT:
      robot.motors.moveRight();
      if (distance > robot.turnDistance)
      {
        robot.direction = Direction::FORWARD;
      }
      break;
    case Direction::LOOKING:
      robot.motors.stop();
      lookController.lookAround(distance);
      break;
    default:
      break;
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
