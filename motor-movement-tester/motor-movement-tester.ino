/******************************************************************************
 * Motors Movement Tester
 *
 * Move motors forward for 2 seconds, then backward for 2 seconds, repeatedly
 * Uses prederminated pin values
 ******************************************************************************/

const int A1A = D8;
const int A1B = D4;
const int B1A = D7;
const int B2A = D2;

void setup()
{
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);

  pinMode(B1A, OUTPUT);
  pinMode(B2A, OUTPUT);
}

void loop()
{
  _moveForward();
  delay(2000);
  _moveBackward();
  delay(2000);
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
