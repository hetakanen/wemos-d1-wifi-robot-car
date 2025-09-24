#include <Arduino.h>
#include "motors.h"

void Motors::setup() {      
    pinMode(A1A, OUTPUT);
    pinMode(A1B, OUTPUT);

    pinMode(B1A, OUTPUT);
    pinMode(B2A, OUTPUT);
}

void Motors::stop() {
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, LOW);
    digitalWrite(B2A, LOW);
}

void Motors::moveLeft() {
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    analogWrite(B1A, speedR);
    digitalWrite(B2A, LOW);
}

void Motors::moveRight() {
    digitalWrite(A1A, LOW);
    analogWrite(A1B, speedL);
    digitalWrite(B1A, LOW);
    digitalWrite(B2A, LOW);
}

void Motors::moveForward() {
    digitalWrite(A1A, LOW);
    analogWrite(A1B, speedL);
    analogWrite(B1A, speedR);
    digitalWrite(B2A, LOW);
}

void Motors::moveBackward() {
    analogWrite(A1A, speedL);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, LOW);
    analogWrite(B2A, speedR);
}
