#include <Servo.h>

Servo myservo;

void setup() {
  // Attach the servo to pin 4
  myservo.attach(4);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Move the servo to 0 degrees
  myservo.write(0);
  delay(1000);

  // Move the servo to 180 degrees
  myservo.write(180);
  delay(1000);
}
