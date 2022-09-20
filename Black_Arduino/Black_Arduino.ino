/*
Read serial data from the computer to the Arduino
*/

int incomingByte = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0){
    incomingByte = Serial.read();
    if (incomingByte == 'a'){
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
    
  }
}
