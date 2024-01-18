// Define the pin number for the relay
int relay = 9;

// Declare a variable to store incoming SMS character
char sms;

// Setup function runs once when the Arduino is powered on or reset
void setup()
{
  // Set the relay pin as an output
  pinMode(relay, OUTPUT);

  // Turn off the relay initially (HIGH level on the pin)
  digitalWrite(relay, HIGH);

  // Start serial communication with a baud rate of 9600
  Serial.begin(9600);
}

// Loop function runs repeatedly as long as the Arduino is powered on
void loop()
{
  // Check if there is any data available to read from the serial port
  if(Serial.available() != 0)
  {
    // Read the incoming character from the serial port and store it in the 'sms' variable
    sms = Serial.read();
  }

  // Check if the received character is 'a'
  if(sms == 'a')
  {
    // If 'a' is received, turn on the relay (LOW level on the pin)
    digitalWrite(relay, LOW);
  }

  // Check if the received character is 'b'
  if(sms == 'b')
  {
    // If 'b' is received, turn off the relay (HIGH level on the pin)
    digitalWrite(relay, HIGH);
  }
}
