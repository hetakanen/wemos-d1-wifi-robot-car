/******************************************************************************
 * Button Pause Function Tester
 *
 * Rules:
 * - Motor changes direction every 2 seconds
 * - Press button to start/pause motor movement
 *
 * Uses prederminated pin values
 ******************************************************************************/

const int BUTTON_PIN = D0;
const int A1A = D8;
const int A1B = D4;
const int B1A = D7;
const int B2A = D2;

const int moveDuration = 2000;
const unsigned long loopDelay = 200;

enum Direction
{
  FORWARD,
  BACKWARD
};

bool buttonEnabled = true;

long lastDirectionChangeTime = 0;
long pauseTime = 0;

bool isRunning = false;
Direction currentDirection = Direction::FORWARD;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);

  pinMode(B1A, OUTPUT);
  pinMode(B2A, OUTPUT);
}

void loop()
{
  const int buttonState = digitalRead(BUTTON_PIN);
  const bool isButtonPressed = buttonState == LOW && buttonEnabled;
  const bool isButtonReleased = buttonState == HIGH;

  long currentTime = millis();

  if (isButtonPressed)
  {
    _onButtonPressed();
    buttonEnabled = false;
  }
  if (isButtonReleased)
  {
    buttonEnabled = true;
  }

  if (isRunning)
  {
    if (currentTime - lastDirectionChangeTime >= moveDuration)
    {
      lastDirectionChangeTime = currentTime;
      _changeDirection();
    }

    switch (currentDirection)
    {
    case Direction::FORWARD:
      _moveForward();
      break;
    case Direction::BACKWARD:
      _moveBackward();
      break;
    default:
      break;
    }
  }
  else
  {
    _stop();
  }

  delay(loopDelay);
}

void _changeDirection()
{
  switch (currentDirection)
  {
  case Direction::FORWARD:
    currentDirection = Direction::BACKWARD;
    break;
  case Direction::BACKWARD:
    currentDirection = Direction::FORWARD;
    break;
  default:
    break;
  }
}

// Sets isRunning boolean status, pause time is applied to movement duration
void _onButtonPressed()
{
  long currentTime = millis();
  isRunning = !isRunning;

  if (isRunning)
  {
    long pauseDuration = currentTime - pauseTime;
    lastDirectionChangeTime += pauseDuration;
  }
  else
  {
    pauseTime = currentTime;
  }
}

void _stop()
{
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B2A, LOW);
}

void _moveForward()
{
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1A, HIGH);
  digitalWrite(B2A, LOW);
}

void _moveBackward()
{
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B2A, HIGH);
}
