int freq = 1000;
int x = 0;
int y = 1;
float z = 3.14; 

void setup() // runs only one time
{
  Serial.begin(9600); // serial comm between arduino and computer (USB)
}

void loop() // runs until you stop it
{
  //Serial.print("Hello Computer, ");
  //Serial.println("My name is Elliot"); // serial print line
  x = x + 1; // only have to define int once in global
  x += 1; // compound operation
  x++; // increment (only adds one)
  y = x * 2;
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);
  delay(freq);
  // other math operations include
  // +, -, *, /, % (modulus)
  // modulo returs remainder from division
  Serial.println(8 % 4);
  Serial.print("z = ");
  Serial.println(z);
  
}