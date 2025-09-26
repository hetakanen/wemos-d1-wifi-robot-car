#include "Robot.h"

Robot robot;

const unsigned long loopDelay = 50;

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
    switch (robot.action)
    {
    case Action::MOVING: {
      float distance = robot.lookController.sensor.readDistance();
      const bool shouldToggle = robot.ledController.getShouldToggle(distance);
      if (shouldToggle)
      {
        robot.ledController.toggle();
      }

      robot.move(distance);
      break;
    }
    case Action::LOOKING:
      robot.stop();
      robot.ledController.off();
      robot.look();
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
