 #include <Servo.h>/*Moving a Cart*/Servo leftWheel; // Left WheelServo rightWheel; // Right Wheelvoid setup() {  leftWheel.attach(11); // attach servo object to pin  rightWheel.attach(3); // attach servo object to pin  delay(1000);}void foreward(){  leftWheel.write(180);  rightWheel.write(0);}void backward(){  leftWheel.write(0);  rightWheel.write(180);}void right(){  leftWheel.write(180);  rightWheel.write(90);}void left(){  leftWheel.write(90);  rightWheel.write(180);}void stop(){  leftWheel.write(96);  rightWheel.write(95);}void loop() {    foreward();  delay(1000);  stop();  delay(10000);}