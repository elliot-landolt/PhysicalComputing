// potentiometer with lights

int val; // value of the pot
int mapval;
int mapval2;

int potPin = A0;

void setup()
{
  for(int i=2; i<=7; i++){ // set up LED's
    pinMode(i, OUTPUT);
  }
  pinMode(potPin, INPUT); // set up pin for potentiometer
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(potPin); // value and reads
  Serial.println(val);
  
  if (val <= 205){ // light one
  digitalWrite(2, HIGH);
  }
  else{
  digitalWrite(2, LOW);
  }
  
  if (val <= 410 and val >= 205){ // light two
  digitalWrite(3, HIGH);
  }
  else{
  digitalWrite(3, LOW);
  }
  
  if (val <= 615 and val >= 410){ // light three
  digitalWrite(4, HIGH);
  }
  else{
  digitalWrite(4, LOW);
  }
  
  if (val <= 820 and val >= 615){ // light four
  digitalWrite(5, HIGH);
  }
  else{
  digitalWrite(5, LOW);
  }
  
  if (val <= 1023 and val >= 820){ // light five
  digitalWrite(6, HIGH);
  }
  else{
  digitalWrite(6, LOW);
  }
  
  if (val <= 50 or val == 1023){ // green flashing light
  digitalWrite(7, HIGH);
  }
  else{
    digitalWrite(7, LOW);
  }
}