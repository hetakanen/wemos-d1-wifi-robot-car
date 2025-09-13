const int echo = D10;
const int trigger = D9;

const float speedOfLight = 0.034;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

// Measure distance with  and print to Serial Monitor
void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  float duration = pulseIn(echo, HIGH);
  float distance = (duration * speedOfLight) / 2;
  Serial.print("DISTANCE ");
  Serial.println(distance);

  delay(100);
}
