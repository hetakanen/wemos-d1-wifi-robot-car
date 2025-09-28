/******************************************************************************
 * Sensor Read Tester
 *
 * HC-SR04 ultrasonic sensor reads current distance and prints it to Serial Monitor
 * Uses prederminated pin values
 ******************************************************************************/

const int echo = D10;
const int trigger = D9;

const float speedOfLight = 0.034;

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  float duration = pulseIn(echo, HIGH);
  float distance = (duration * speedOfLight) / 2;
  Serial.print("DISTANCE ");
  Serial.println(distance);

  delay(100);
}
