#include "pauseButton.h"

void PauseButton::setup() {
    pinMode(BUTTON, INPUT);
}

bool PauseButton::isPressed() {
    const int buttonState = digitalRead(BUTTON);

    const bool isPressed = buttonEnabled && buttonState == LOW;
    if(buttonState == HIGH) {
        buttonEnabled = true;
    } else {
        buttonEnabled = false;
    }

    return isPressed;
}
