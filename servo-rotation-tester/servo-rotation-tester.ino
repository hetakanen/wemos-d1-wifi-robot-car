/******************************************************************************
 * Servo Rotation Tester
 *
 * Allow user to give rotation value for SG90 servo via Serial Monitor
 * Requires Servo.h library
 * Uses prederminated pin values
 ******************************************************************************/

#include <Servo.h>

Servo myservo;

const int PIN = D3;
const int LEFT = 2200;
const int RIGHT = 1200;
const int CENTER = 1750;

void setup()
{
  Serial.begin(9600);
  myservo.attach(PIN, RIGHT, LEFT);
  myservo.write(CENTER);
}

void loop()
{
  int val = Serial.parseInt();
  Serial.println(val);
  if (val != 0)
  {
    myservo.write(val);
  }
  delay(2000);
}
