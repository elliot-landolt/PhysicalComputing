/*
Read and use a potentiometer 
*/

int potPin = A0; // potentiometer wiper pin
int val; // value of the potPin

int spkPin = 3;

void setup() {
    pinMode(potPin, INPUT);
    Serial.begin(9600);
    pinMode(spkPin, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop() {
   val = analogRead(potPin);
   //val = constrain(val, 100, 900); // constrain val from 100 to 900
   val = map(val, 100, 1000, 200, 800);
   
   Serial.println(val);
   delay(20);
   
   tone(spkPin, val);
   
   analogWrite(5, val/4);
}