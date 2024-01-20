#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Arduino.h>
#include "HX711.h"

// Initialize NFC and HX711 objects
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
HX711 scale;

// Constants and variables
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
int buzzerPin = 12;
float itemInitialWeight = 58.00;
int itemCount = 0;
float currentWeight;
float previousWeight;
bool isUserVerified = false;

// List of authorized NFC UIDs
String authorizedUIDs[] = { "0D 8A 7B 38", "04 48 B3 AA 5D 63 80", "43 5E 31 1B" };

// Setup function
void setup(void) {
  // Start serial communication
  Serial.begin(9600);
  Serial.println("System initialized");

  // Initialize NFC and HX711
  nfc.begin();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  // Set the scale factor and tare the scale
  scale.set_scale(-459.542);
  scale.tare();

  // Print readings to serial monitor
  Serial.println("Readings:");

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
}

// Main loop
void loop() {
  // Print initial item weight
  Serial.println("itemInitialWeight: " + String(itemInitialWeight));

  // If user is not verified, attempt verification
  if (!isUserVerified) {
    isUserVerified = verifyUser();
  }

  // Measure weight
  weightMeasure();
}

// Turn on the buzzer
void turnOnTheBuzzer() {
  digitalWrite(buzzerPin, HIGH);
}

// Turn off the buzzer
void turnOffTheBuzzer() {
  digitalWrite(buzzerPin, LOW);
}

// Read NFC tag and return UID
String readNFC() {
  String tagID = "";

  // Check if an NFC tag is present
  if (nfc.tagPresent()) {
    // Read the NFC tag and get its UID
    NfcTag tag = nfc.read();
    tagID = tag.getUidString();
  } else {
    Serial.println("No Tags Found");
  }

  return tagID;
}

// Verify the user based on NFC UID
boolean verifyUser() {
  String readID = readNFC();

  // Check if a valid UID is read
  if (readID.length() != 0) {
    // Iterate through authorized UIDs
    for (int i = 0; i < sizeof(authorizedUIDs); i++) {
      // Check if the read UID matches an authorized UID
      if (readID == authorizedUIDs[i]) {
        // Grant access and print message
        Serial.println("Access granted and now you can pick the item");
        weightMeasure();
        return true;
      } else {
        // Deny access and print message
        Serial.println("Access Denied");
        return false;
      }
    }
  }

  return false;
}

// Measure weight and perform actions based on weight changes
void weightMeasure() {
  // Get the current weight from the scale
  float currentWeight = scale.get_units();
  Serial.println("This is the current weight: " + String(currentWeight));

  // Calculate the ratio of current weight to the initial item weight
  int weightRatio = currentWeight / itemInitialWeight;
  Serial.println("This is the weight ratio (itemCount): " + String(weightRatio));

  // Handle different weight scenarios
  if (itemCount == 0) {
    // Set initial item count
    itemCount = weightRatio;
    Serial.println("Initial item count: " + String(itemCount));
  } else if (weightRatio == itemCount) {
    // No item has been picked, turn off the buzzer
    Serial.println("No item has been picked");
    turnOffTheBuzzer();
  } else if (weightRatio > itemCount) {
    // New item has been added to the shelf, reset item count
    Serial.println("New item has been added to the shelf");
    itemCount = 0;
  } else if (weightRatio < itemCount) {
    // Item has been picked
    if (!isUserVerified) {
      // If user is not verified, turn on the buzzer
      turnOnTheBuzzer();
      return;
    }

    // Print message and reset item count
    Serial.println("The item has been picked");
    isUserVerified = false;
    itemCount = weightRatio;
  }

  // Delay for stability
  delay(1000);
}
