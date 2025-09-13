class Motors {
    public:
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
};