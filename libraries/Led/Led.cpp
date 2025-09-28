#include "led.h"

void Led::setup() {      
    pinMode(PIN, OUTPUT);
}

void Led::toggle() {
    analogWrite(PIN, isLedOn ? LED_OFF : LED_ON);
    isLedOn = !isLedOn;
}

void Led::on() {
    analogWrite(PIN, LED_ON);
    isLedOn = true;
}

void Led::off() {
    analogWrite(PIN, LED_OFF);
    isLedOn = false;
}