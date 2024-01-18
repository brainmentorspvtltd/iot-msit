// Define pins for the ultrasonic sensor
int buzzPin = 11;
int echoPin = 13;
int trigPin = 12;

// Setup function, runs once when the Arduino starts
void setup() {
  // Start serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Print a welcome message to the serial monitor
  Serial.println("Hello there!");
  
  // Set pin modes for the ultrasonic sensor
  pinMode(buzzPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

// Loop function, runs repeatedly after setup
void loop() {
  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the pulse to return
  // The value of time will be in microseconds
  int time = pulseIn(echoPin, HIGH);

  // Calculate distance based on the speed of sound (343 m/s) and the formula: distance = speed * time
  // The factor 0.034 converts time from microseconds to centimeters (343 m/s * 0.034 cm/microsec)
  int distance = (0.034 * time) / 2;

  // Print the calculated distance to the Serial Monitor
  Serial.println(distance);

  // Call the function to control the buzzer based on the calculated distance
  controlBuzzer(distance);

  // Main code continues to run repeatedly in the loop
}

// Function to control the buzzer based on the calculated distance
void controlBuzzer(int distance) {
  int delayDuration = 0;

  // Set delay duration based on distance ranges
  if (distance <= 10) {
    delayDuration = 50;
  } else if (distance > 10 && distance <= 50) {
    delayDuration = 100;
  } else if (distance > 50 && distance <= 70) {
    delayDuration = 200;
  } else if (distance > 70 && distance <= 100) {
    delayDuration = 500;
  }

  // Turn the buzzer on and off with specified delay duration
  turnBuzzerOn();
  delay(delayDuration);
  turnBuzzerOff();
  delay(50); // Additional delay for stability
}

// Function to turn the buzzer on
void turnBuzzerOn() {
  digitalWrite(buzzPin, HIGH);
}

// Function to turn the buzzer off
void turnBuzzerOff() {
  digitalWrite(buzzPin, LOW);
}
