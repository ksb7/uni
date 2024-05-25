#include <ESP8266WiFi.h>
#include "DHT.h"

const int DHTPIN = s8;
#define DHTTYPE DHT11

#define LED1 1
#define LED2 2
#define LED3 3

#define GAS_SENSOR D4
#define TRIGGER_PIN D5
#define ECHO_PIN D6

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read gas level
  int gasLevel = analogRead(GAS_SENSOR);

  // Read distance from ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  // Control LEDs based on sensor data
  if (temperature > 25 || humidity > 70) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (gasLevel > 500) { // Adjust threshold as needed
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }

  if (distance < 20) { // Object detected within 20 cm
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }

  // Print sensor data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" %\tGas Level: ");
  Serial.print(gasLevel);
  Serial.print("\tDistance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(2000); // Adjust delay as needed
}
