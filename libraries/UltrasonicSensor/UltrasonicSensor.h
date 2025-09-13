#include <Servo.h>

class UltrasonicSensor {
    public:
        void setup();
        float readDistance();
    private:  
        const int ECHO = D10;
        const int TRIGGER = D9;
        const int SERVO = D3;

        const int LEFT = 2200;
        const int RIGHT = 1200;
        const int CENTER = 1750;

        Servo myservo;
};
