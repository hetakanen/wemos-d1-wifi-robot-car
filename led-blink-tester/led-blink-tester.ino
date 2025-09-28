/******************************************************************************
 * LED Blink Tester
 *
 * Program tests LED blink by making an LED blink on and off at 1-second intervals.
 *
 * Uses prederminated pin values
 ******************************************************************************/

const int LED = D12;

void setup()
{
  pinMode(LED, OUTPUT);
}

void loop()
{
  analogWrite(LED, 255);
  delay(1000);
  analogWrite(LED, 0);
  delay(1000);
}
