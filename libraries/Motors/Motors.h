#pragma once
#include <Arduino.h>

class Motors {
    public:
        Motors(int a1aPin, int a1bPin, int b1aPin, int b2aPin, int pwmLSpeed, int pwmRSpeed)
            : A1A(a1aPin), A1B(a1bPin), B1A(b1aPin), B2A(b2aPin), speedL(pwmLSpeed), speedR(pwmRSpeed) {}
        Motors(int pwmLSpeed, int pwmRSpeed) : speedL(pwmLSpeed), speedR(pwmRSpeed) {}
        Motors(int pwmSpeed) : speedL(pwmSpeed), speedR(pwmSpeed) {}
        Motors() {}
        void setup();
        void stop();
        void moveLeft();
        void moveRight();
        void moveForward();
        void moveBackward();
    private:
        const int A1A = D8;
        const int A1B = D4;
        const int B1A = D7;
        const int B2A = D2;
        const int speedL = 200; //PWM speed 0-255
        const int speedR = 200; //PWM speed 0-255
};
