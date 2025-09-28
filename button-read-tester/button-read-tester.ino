/******************************************************************************
 * Button Read Tester
 *
 * Read current button state and print to Serial Monitor
 * Uses prederminated pin values
 ******************************************************************************/

const int BUTTON_PIN = D0;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  int buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);
  delay(500);
}