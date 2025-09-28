/******************************************************************************
 * Servo Min to Max Tester
 *
 * Rotate HC-SR04 ultrasonic sensor from min to max rotation using SG90 servo
 * Requires Servo.h library
 * Uses prederminated pin values
 ******************************************************************************/

#include <Servo.h>

Servo myServo;
const int PIN = D3;

void setup()
{
  myServo.attach(PIN, 1200, 2200);
  Serial.begin(9600);
}

void loop()
{
  for (int us = 1200; us <= 2200; us += 100)
  {
    myServo.writeMicroseconds(us);
    delay(500);
    Serial.println(us);
  }
  while (true)
    ;
}