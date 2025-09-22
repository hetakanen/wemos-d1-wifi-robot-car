#pragma once
#include <Arduino.h>

class PauseButton {
    public:
        PauseButton(int buttonPin = D0) : BUTTON(buttonPin) {}
        void setup();
        bool isPressed();
    private:
        const int BUTTON;
        bool buttonEnabled = true;
};
