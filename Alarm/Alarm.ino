/*
ALARM
*/

int spkPin = 13;

void setup() {
  pinMode(spkPin, OUTPUT);
}

void loop() {
  digitalWrite(spkPin, HIGH);
  delay(5000);
  digitalWrite(spkPin, LOW);
  delay(3000);
}
