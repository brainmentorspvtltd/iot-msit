#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Firebase database configuration
#define FIREBASE_HOST "esp8266-msit-3-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "P21qTRfmGuLRfzFpnEy7eOE2BHHhLIu4CGxdFJcM"

// WiFi credentials
#define WIFI_SSID "UpsideDown"
#define WIFI_PASSWORD "flipkart"

// Pin configuration
int ledPin = 5;  // GPIO5 corresponds to D1 on NodeMCU

void setup() {
  Serial.begin(9600);

  // Set the pin mode for the LED
  pinMode(ledPin, OUTPUT);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting");
    delay(500);
  }
  Serial.println("Connected!!!");

  // Initialize Firebase connection and set an initial value in the database
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("temp_val", 45);
}

void loop() {
  // Retrieve data from Firebase database
  int data = Firebase.getInt("temp_val");

  // Check the retrieved data and control the LED accordingly
  if (data == 45) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  } else if(data == 46) {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  }

  // Delay for 1 second before the next iteration
  delay(1000);
}
