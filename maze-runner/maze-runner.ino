#include <UltrasonicSensor.h>
#include <Motors.h>
#include <PauseButton.h>
#include <Led.h>

UltrasonicSensor sensor;
Motors motors;
PauseButton pauseButton;
Led led;

typedef void (*CallbackType)(float);

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

long lastChangedTime = 0;

struct Robot {
  Direction direction;
  Looking looking;
  bool isRunning;
};

Robot robot;
void setup() {
  sensor.setup();
  motors.setup();
  pauseButton.setup();
  led.setup();
  lastChangedTime = millis();

  robot = {Direction::FORWARD, Looking::LOOK_CENTER, false};
}

void loop() {
  const bool isButtonPressed = pauseButton.isPressed();
  if (isButtonPressed) {
    robot.isRunning = !robot.isRunning;
  }

  if (robot.isRunning) {
    const float distance = sensor.readDistance();
    handleLed(distance);
    
    if (robot.direction == Direction::FORWARD || robot.direction == Direction::BACKWARD) {
      if (distance < minDistance) {
        robot.direction = Direction::BACKWARD;
      } else if (distance < turnDistance) {
        robot.direction = Direction::LOOKING;
        robot.looking = Looking::LOOK_LEFT;
      } else {
        robot.direction = Direction::FORWARD;
      }
    }

    switch (robot.direction) {
      case Direction::FORWARD:
        motors.moveForward();
        break;
      case Direction::BACKWARD:
        motors.moveBackward();
        break;
      case Direction::LEFT:
        motors.moveLeft();
        if(distance > turnDistance) {
          robot.direction = Direction::FORWARD;
        }
        break;
      case Direction::RIGHT:
        motors.moveRight();
        if(distance > turnDistance) {
          robot.direction = Direction::FORWARD;
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
    led.off();
  }

  delay(loopDelay);
}

void handleLed(float distance) {
  const long currentTime = millis();
  const bool shouldToggleLed = currentTime - lastChangedTime >= distance * 10;

  if(shouldToggleLed) {
    led.toggle();
    lastChangedTime = millis();
  }
}

class Distance {
  public:
    int rotation;
    float distance;
};
Distance longestDistance;
void findDirection(float distance) {
  switch (robot.looking) {
    case Looking::LOOK_LEFT:
      lookAt(sensor.LEFT, [](float d) {
        if(d > longestDistance.distance) {
          longestDistance.distance = d;
          longestDistance.rotation = sensor.LEFT;
        }
        robot.looking = Looking::LOOK_RIGHT;
      }, distance);
      break;
    case Looking::LOOK_CENTER:
      lookAt(sensor.CENTER, [](float d) {
        if(longestDistance.distance < turnDistance) {
          robot.direction = Direction::BACKWARD;
        }
        else if(longestDistance.rotation == sensor.LEFT) {
          robot.direction = Direction::LEFT;
        }
        else if(longestDistance.rotation == sensor.RIGHT) {
          robot.direction = Direction::RIGHT;
        }
        else {
          robot.direction = Direction::BACKWARD;
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
        robot.looking = Looking::LOOK_CENTER;
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
