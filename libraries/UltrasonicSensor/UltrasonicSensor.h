#pragma once
#include <Servo.h>
#include <Arduino.h>

class UltrasonicSensor {
    public:
        UltrasonicSensor(int echoPin = D10, int triggerPin = D9, int servoPin = D3)
            : ECHO(echoPin), TRIGGER(triggerPin), SERVO(servoPin) {}
        void setup();
        float readDistance();
        int getRotation();
        void lookAt(int value);
        const int LEFT = 2200;
        const int RIGHT = 1200;
        const int CENTER = 1750;
    private:
        const int ECHO;
        const int TRIGGER;
        const int SERVO;
        Servo myservo;
};
