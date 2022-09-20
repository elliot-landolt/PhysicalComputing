/*
Double Click Game
*/

int buttonPin = 2; // button pin
int buttonState = LOW; // is the button pushed?
int spkPin = 13;
int ledState = LOW;
long timeNow = 0;
long delta = 0;



void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  pinMode(spkPin, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, ledState);
}


void loop() {
  
  if(debounceButton(buttonState) == HIGH && buttonState == LOW){
    // code only runs once when button is pressed down
    buttonState = HIGH;
    //ledState = !ledState; // not the led state (High set to Low)
    delta = millis() - timeNow;
    timeNow = millis();
    Serial.println(delta);
    if (delta >= 4000 and delta <= 5500){
      digitalWrite(6, HIGH);
      tone(spkPin, 146.83, 200); // D3
      delay(400);
      tone(spkPin, 293.66, 150); // D4
      delay(300);
      tone(spkPin, 130.81, 50); // C3
      delay(200);
      tone(spkPin, 130.81, 50); // C3
      delay(200);
      tone(spkPin, 261.63, 100); // C4
      delay(200);
      tone(spkPin, 220.00, 100); // A3
      delay(125);
      tone(spkPin, 196.00, 100); // G3
      delay(125);
      tone(spkPin, 174.61, 100); // F3
      delay(125);
      tone(spkPin, 196.00, 100); // G3
    }
    else{
      digitalWrite(6, LOW);
    }
  }
  
  else if (debounceButton(buttonState) == LOW && buttonState == HIGH){
    // code only runs once when button is released
    buttonState = LOW;
    
  }
  //digitalWrite(6, ledState);  
}  


bool debounceButton(bool state){
  bool stateNow = digitalRead(buttonPin);
  if (state != stateNow){
    delay(10);
    stateNow = digitalRead(buttonPin);
    
  }
  return stateNow;
  
}