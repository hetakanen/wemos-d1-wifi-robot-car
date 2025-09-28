/******************************************************************************
 * Obstacle-Avoiding Robot Car
 * - Uses an ultrasonic sensor to measure distance while moving
 * - If an obstacle is detected nearby, the car stops and uses servo to scan 
 *   left, right, and center
 * - It determines the direction with the most clearance and turns accordingly
 * - If too close to an obstacle, the car moves backward
 * - Blinking LED indicates distance to obstacle
 * - Power can be toggled on/off with a button
 ******************************************************************************/

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
