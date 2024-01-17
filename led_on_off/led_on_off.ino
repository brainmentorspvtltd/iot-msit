// Define the pin for the LED
int ledPin = 13;

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn on the LED
  digitalWrite(ledPin, HIGH);
  
  // Wait for a moment (you can adjust the delay duration)
  delay(1000);

  // Turn off the LED
  digitalWrite(ledPin, LOW);

  // Wait for a moment again
  delay(1000);
}
