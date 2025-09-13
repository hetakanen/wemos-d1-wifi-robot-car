class Motors {
    public:
        Motors(int a1aPin = D8, int a1bPin = D4, int b1aPin = D7, int b2aPin = D2, int pwmSpeed = 200)
            : A1A(a1aPin), A1B(a1bPin), B1A(b1aPin), B2A(b2aPin), speed(pwmSpeed) {}
        void setup();
        void stop();
        void moveLeft();
        void moveRight();
        void moveForward();
        void moveBackward();
    private:
        const int A1A;
        const int A1B;
        const int B1A;
        const int B2A;
        const int speed; //PWM speed 0-255
};
