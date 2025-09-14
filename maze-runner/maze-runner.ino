#include <UltrasonicSensor.h>
#include <Motors.h>
#include <PauseButton.h>

UltrasonicSensor sensor;
Motors motors;
PauseButton pauseButton;

typedef void (*CallbackType)(float);

class Distance {
  public:
    int rotation;
    float distance;
};

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  LOOKING
};

enum Looking {
  LOOK_LEFT,
  LOOK_CENTER,
  LOOK_RIGHT
};

const unsigned long loopDelay = 200;
const float turnDistance = 20.0;
const float minDistance = 10.0;

Direction currentDirection;
Looking currentLooking;

bool isRunning = false;

void setup() {
  sensor.setup();
  motors.setup();
  pauseButton.setup();

  currentDirection = Direction::FORWARD;
  currentLooking = Looking::LOOK_CENTER;
}

void loop() {
  const bool isButtonPressed = pauseButton.isPressed();
  if (isButtonPressed) {
    isRunning = !isRunning;
  }

  const float distance = sensor.readDistance();
  if (isRunning) {
    if (currentDirection == Direction::FORWARD || currentDirection == Direction::BACKWARD) {
      if (distance < minDistance) {
        currentDirection = Direction::BACKWARD;
      } else if (distance < turnDistance) {
        currentDirection = Direction::LOOKING;
        currentLooking = Looking::LOOK_LEFT;
      } else {
        currentDirection = Direction::FORWARD;
      }
    }

    switch (currentDirection) {
      case Direction::FORWARD:
        motors.moveForward();
        break;
      case Direction::BACKWARD:
        motors.moveBackward();
        break;
      case Direction::LEFT:
        motors.moveLeft();
        if(distance > turnDistance) {
          currentDirection = Direction::FORWARD;
        }
        break;
      case Direction::RIGHT:
        motors.moveRight();
        if(distance > turnDistance) {
          currentDirection = Direction::FORWARD;
        }
        break;
      case Direction::LOOKING:
        motors.stop();
        findDirection(distance);
        break;
      default:
        break;
    }
  } else {
    motors.stop();
  }

  delay(loopDelay);
}

Distance longestDistance;
void findDirection(float distance) {
  switch (currentLooking) {
    case Looking::LOOK_LEFT:
      lookAt(sensor.LEFT, [](float d) {
        if(d > longestDistance.distance) {
          longestDistance.distance = d;
          longestDistance.rotation = sensor.LEFT;
        }
        currentLooking = Looking::LOOK_RIGHT;
      }, distance);
      break;
    case Looking::LOOK_CENTER:
      lookAt(sensor.CENTER, [](float d) {
        if(longestDistance.distance < turnDistance) {
          currentDirection = Direction::BACKWARD;
        }
        else if(longestDistance.rotation == sensor.LEFT) {
          currentDirection = Direction::LEFT;
        }
        else if(longestDistance.rotation == sensor.RIGHT) {
          currentDirection = Direction::RIGHT;
        }
        else {
          currentDirection = Direction::BACKWARD;
        }
        longestDistance.distance = -1;
        longestDistance.rotation = -1;
      }, distance);
      break;
    case Looking::LOOK_RIGHT:
      lookAt(sensor.RIGHT, [](float d) {
        if(d > longestDistance.distance) {
          longestDistance.distance = d;
          longestDistance.rotation = sensor.RIGHT;
        }
        currentLooking = Looking::LOOK_CENTER;
      }, distance);
      break;
    default:
      break;
  }
}

void lookAt(int direction, CallbackType callback, float distance) {
  const int rotation = sensor.getRotation();
  if (rotation != direction) {
    sensor.lookAt(direction);
  } else {
    callback(distance);
  }
}
