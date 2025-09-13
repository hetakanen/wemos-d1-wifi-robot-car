class PauseButton {
    public:
        void setup();
        bool isPressed();
    private:  
        const int BUTTON = D0;
        bool buttonEnabled = true;
};