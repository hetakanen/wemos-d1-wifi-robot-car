#include "ultrasonicSensor.h"

void UltrasonicSensor::setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  myservo.attach(SERVO, RIGHT, LEFT);
  myservo.write(CENTER);
}

float UltrasonicSensor::readDistance() {
  const float speedOfLight = 0.034;

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  float duration = pulseIn(ECHO, HIGH);
  return (duration * speedOfLight) / 2;
}