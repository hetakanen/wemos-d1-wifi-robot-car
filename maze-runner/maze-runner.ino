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

    switch (robot.action)
    {
    case Action::MOVING:
      checkObstacles(distance);
      move();
      break;
    case Action::LOOKING:
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

void checkObstacles(float distance)
{
  const bool isTurning = robot.moving == Direction::TURN_LEFT || robot.moving == Direction::TURN_RIGHT;
  if (isTurning)
  {
    if (distance > robot.turnDistance)
    {
      robot.moving = Direction::FORWARD;
    }
  }
  else
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
}

void move()
{
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
    break;
  case Direction::TURN_RIGHT:
    robot.motors.moveRight();
    break;
  default:
    break;
  }
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
