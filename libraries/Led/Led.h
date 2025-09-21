class Led {
    public:
        Led(int pin)
            : PIN(pin) {}
        Led()
            : Led(D12) {}
        void setup();
        void toggle();
        void on();
        void off();
    private:
        const int PIN;
        const int LED_OFF = 0;
        const int LED_ON = 255;
        bool isLedOn = false;
};
