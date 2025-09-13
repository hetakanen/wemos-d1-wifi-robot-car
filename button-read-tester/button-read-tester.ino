
const int BUTTON_PIN = D0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
}

// Read button state and print to Serial Monitors
void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
   Serial.println(buttonState);
   delay(500);
}