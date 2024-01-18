// Define the pin number for the LED
int ledPin = 13;

// Setup function, runs once when the Arduino starts
void setup() {
  // Start serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Print a message to the serial monitor
  Serial.println("HELLO THERE!!");
  
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

// Loop function, runs repeatedly after setup
void loop() {
  // Read data from the serial port
  int data = Serial.read();

  // Check if the received data is '1'
  if (data == '1') {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    
    // Print a message to the serial monitor
    Serial.println("LED IS NOW ON!");
  }

  // Check if the received data is '2'
  if (data == '2') {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
    
    // Print a message to the serial monitor
    Serial.println("LED IS NOW OFF!");
  }

  // Main code continues to run repeatedly in the loop
}
