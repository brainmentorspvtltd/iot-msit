#include "DHT.h"

// Define the pin for the DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11

DHT TH(DHTPIN, DHTTYPE);
int temp;
int humidity;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize the DHT sensor
  TH.begin();
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  temp = TH.readTemperature();
  humidity = TH.readHumidity();
  
  // Print temperature and humidity to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Delay for a short period before taking the next reading
  delay(2000);
}
