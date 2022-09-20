#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
LCD Distance instrument
By: Elliot Landolt
This device reads a distance and then prints it to an lcd.
Additionally, there is also an led that lights up whenever the distance is greater than 5 inches
*/

int triggerPin = 4;
int echoPin = 7;
long echoTime;
float cm = 0; // centimeters
float inch = 0; // inches
int inch2 = 0; // the rounded inch

LiquidCrystal_I2C lcd(0x27,16,2); // call library lcd(set LCD address, 16 width, 2 lines display)
void setup() {
  lcd.init(); // start the lcd
  lcd.backlight();
  lcd.setCursor(0,0); // start of line 1
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 cm = getDistance(triggerPin, echoPin);
 inch = cm / 2.54; // find the inches
 inch2 = round(inch); // round the inches to a whole number
 if (inch2 > 5){
  digitalWrite(13, HIGH); 
 }
 else{
  digitalWrite(13, LOW); 
 }
 lcd.print(inch2); // print the rounded inch
 lcd.setCursor(5,0); // move the cursor to the right
 lcd.print(" Inches"); 
 lcd.setCursor(0,1); // start of the second line
 lcd.print(cm); // print centimeters
 lcd.setCursor(3,1);
 lcd.print(" Centimeters");
 delay(3000);
 lcd.clear(); // clear the screen for the next reading
 delay(500);
}

float getDistance(int ping, int echo){ // this function gets the distance from the sensor
 digitalWrite(ping, LOW);
 delayMicroseconds(2);
 // send out our ping
 digitalWrite(ping, HIGH);
 delayMicroseconds(10);
 digitalWrite(ping, LOW);
 long echoTime = pulseIn(echo, HIGH);
 float cm = echoTime * 0.03 / 2; // divide by two beause the sensor accounts for the "going and coming"
 return cm;
}