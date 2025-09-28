/******************************************************************************
 * Vacuum - Simple robot car
 *
 * Rules:
  * 1. Run/stop with button
  * 2. Turn left when distance low
  * 3. Go backwards when distance very low
  * 4. Otherwise go forward

 * Requires Servo.h library
 * Expects following custom libraries to be attached under sketchbook /libraries
  * - Motor
  * - UltrasonicSensor
  * - PauseButton
 * Uses prederminated pin values
 ******************************************************************************/

#include <UltrasonicSensor.h>
#include <Motors.h>
#include <PauseButton.h>

UltrasonicSensor sensor;
Motors motors;
PauseButton pauseButton;

const unsigned long loopDelay = 200;
const int turnDistance = 20;
const int minDistance = 10;

enum Direction
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  LOOKING
};
Direction currentDirection = Direction::FORWARD;

bool isRunning = false;

void setup()
{
  sensor.setup();
  motors.setup();
  pauseButton.setup();
}

void loop()
{
  const bool isButtonPressed = pauseButton.isPressed();
  if (isButtonPressed)
  {
    isRunning = !isRunning;
  }

  if (isRunning)
  {
    const float distance = sensor.readDistance();
    if (distance < minDistance)
    {
      currentDirection = Direction::BACKWARD;
    }
    else if (distance < turnDistance)
    {
      currentDirection = Direction::LEFT;
    }
    else
    {
      currentDirection = Direction::FORWARD;
    }

    switch (currentDirection)
    {
    case Direction::FORWARD:
      motors.moveForward();
      break;
    case Direction::BACKWARD:
      motors.moveBackward();
      break;
    case Direction::LEFT:
      motors.moveLeft();
      break;
    case Direction::RIGHT:
      motors.moveRight();
      break;
    default:
      break;
    }
  }
  else
  {
    motors.stop();
  }

  delay(loopDelay);
}
