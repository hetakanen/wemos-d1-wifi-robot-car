#include <Servo.h>

Servo myservo;

const int PIN = D3
void setup() {
  Serial.begin(9600);
  myservo.attach(PIN, 1200, 2200);
  myservo.write(110);
}

// Allow user to give rotation value for SG90 servo via Serial Monitor
void loop() {
  int val = Serial.parseInt();
  Serial.println(val);
  if(val != 0) {
      myservo.write(val);
    }
  delay(2000);
}
