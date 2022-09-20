/*
multiline comment
*/

int ledPin = 13; // variable named ledPin with a value of 13
int freq = 1000;
int x = 0;
int y = 1;

void setup() // runs only one time
{
  pinMode(ledPin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600); // serial comm between arduino and computer (USB)
}

void loop() // runs until you stop it
{
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  delay(freq / 10);
  digitalWrite(ledPin, HIGH);
  delay(freq);
  
  
  //Serial.print("Hello Computer, ");
  //Serial.println("My name is Elliot"); // serial print line
  x = x + 1; // only have to define int once in global
  x += 1; // compound operation
  x++; // increment (only adds one)
  y = x * 2;
  Serial.print("y = ");
  Serial.println(y);
  Serial.print("x = ");
  Serial.println(x);
  // other math operations include
  // +, -, *, /, % (modulus)
  
  digitalWrite(12, LOW);
  delay(freq / 10);
  digitalWrite(ledPin, LOW);
  digitalWrite(11, LOW);
  delay(freq);
}