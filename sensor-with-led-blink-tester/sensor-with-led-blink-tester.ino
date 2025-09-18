/******************************************************************************
 * LED Blink by Sensor Distance Tester
 * 
 * Program tests LED blink by measuring distance using an ultrasonic sensor and adjusting the blink rate
 * The longer the measured distance, the longer the LED stays in each state (on/off).
 *
 ******************************************************************************/

#include <UltrasonicSensor.h>

const int LED_PIN = D12;
const int LED_OFF = 0;
const int LED_ON = 255;
const int DISTANCE_MULTIPLIER = 10; 

UltrasonicSensor sensor;

bool isLedOn = false;
long lastChangedTime = 0;

void toggleLed() {
  analogWrite(LED_PIN, isLedOn ? LED_OFF : LED_ON);
  isLedOn = !isLedOn;
  lastChangedTime = millis();
}

void setup() {
  Serial.begin(9600);
  sensor.setup();
  pinMode(LED_PIN, OUTPUT);
  lastChangedTime = millis();
}

void loop() {
  const float distance = sensor.readDistance();
  const long currentTime = millis();
  const bool shouldToggleLed = currentTime - lastChangedTime >= distance * DISTANCE_MULTIPLIER;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(shouldToggleLed) {
    toggleLed();
  }
  
  delay(100);
}
