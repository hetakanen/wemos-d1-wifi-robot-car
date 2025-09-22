#include "Robot.h"

Robot robot;

const unsigned long loopDelay = 200;

void setup()
{
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
    const float distance = robot.lookController.sensor.readDistance();
    const bool shouldToggle = robot.ledController.getShouldToggle(distance);
    if (shouldToggle)
    {
      robot.ledController.toggle();
    }

    switch (robot.action)
    {
    case Action::MOVING:
      robot.move(distance);
      break;
    case Action::LOOKING:
      robot.stop();
      robot.look(distance);
      break;
    default:
      break;
    }
  }
  else
  {
    robot.stop();
  }

  delay(loopDelay);
}
