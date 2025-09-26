#include "ultrasonicSensor.h"

void UltrasonicSensor::setup()
{
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  myservo.attach(SERVO, RIGHT, LEFT);
  myservo.write(CENTER);
}

float UltrasonicSensor::readDistance()
{
  const float speedOfLight = 0.034;

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  float duration = pulseIn(ECHO, HIGH);
  return (duration * speedOfLight) / 2;
}

void UltrasonicSensor::lookAt(int value)
{
  myservo.writeMicroseconds(value);
}

int UltrasonicSensor::getRotation()
{
  return myservo.readMicroseconds();
}

void UltrasonicSensor::addDelay(int value)
{
  delay(value);
}