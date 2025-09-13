# Requirements

Expects following libraries to be installed:
- ESP8266 (custom library not provided by Arduino library manager)
- Servo

Expects following custom libraries to be attached under sketchbook /libraries
- Motor
- UltrasonicSensor
- PauseButton

# Functionalities

Rules:
1. Run/stop with button
2. Turn left when distance low
3. Go backwards when distance very low
4. Otherwise go forward