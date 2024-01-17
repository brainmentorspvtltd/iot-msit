// Define the pins for the ultrasonic sensor
int echoPin = 13;
int trigPin = 12;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes for the ultrasonic sensor
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the pulse to return
  // The value of time will be in microseconds
  int time = pulseIn(echoPin, HIGH);

  // Calculate distance based on the speed of sound (343 m/s) and the formula: distance = speed * time
  // The factor 0.034 converts time from microseconds to centimeters (343 m/s * 0.034 cm/microsec)
  int distance = 0.034 * time;

  // Print the calculated distance to the Serial Monitor
  Serial.println(distance);

  // Main code runs repeatedly in the loop
}
