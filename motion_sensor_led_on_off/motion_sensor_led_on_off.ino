// Define the pin for the PIR sensor
int pirPin = 2;

// Define the pin for the LED
int ledPin = 13;

void setup() {
  // Set the PIR pin as an input
  pinMode(pirPin, INPUT);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the PIR sensor value
  int pirValue = digitalRead(pirPin);

  // Print the PIR sensor value to the Serial Monitor
  Serial.println(pirValue);

  // Check if motion is detected
  if (pirValue == HIGH) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }

  // Add a delay to avoid rapid on/off switching due to sensor noise
  delay(500);
}
