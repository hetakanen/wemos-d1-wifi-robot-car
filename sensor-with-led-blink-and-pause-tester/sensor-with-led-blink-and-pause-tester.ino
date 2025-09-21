/******************************************************************************
  * Sensor with LED Blink and Pause Tester
  * Tests that ultrasonic sensor, LED and pause button can be used at the same time
 ******************************************************************************/

#include <UltrasonicSensor.h>
#include <PauseButton.h>
#include <Led.h>

UltrasonicSensor sensor;
PauseButton pauseButton;
Led led;

long lastLedChangedTime = 0;
bool isRunning = false;

void setup() {
  Serial.begin(9600);
  sensor.setup();
  pauseButton.setup();
  led.setup();
  lastLedChangedTime = millis();
}

void loop() {
  const bool isButtonPressed = pauseButton.isPressed();
  if (isButtonPressed) {
    isRunning = !isRunning;
  }

  if(isRunning) {
    if(getShouldToggleLed()) {
      led.toggle();
      lastLedChangedTime = millis();
    }
  } else {
    led.off();
  }
  
  delay(100);
}

bool getShouldToggleLed() {
  const int DISTANCE_MULTIPLIER = 10; 
  const float distance = sensor.readDistance();
  
  Serial.print("Distance: ");
  Serial.println(distance);

  const long currentTime = millis();
  return currentTime - lastLedChangedTime >= distance * DISTANCE_MULTIPLIER;
}
