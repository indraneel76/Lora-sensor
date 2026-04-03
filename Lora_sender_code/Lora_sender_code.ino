#include <SPI.h>
#include <LoRa.h>

// LoRa control pins
#define SS_PIN   10
#define RST_PIN   9
#define DIO0_PIN  2
#include "DHT.h"

// =========================
// DHT settings
// =========================
#define DHTPIN 12        // DHT11 data pin connected to D2
#define DHTTYPE DHT11    // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);




// SX1278 usually works at 433E6
#define LORA_FREQUENCY 433E6

int counter = 0;
String message ;
void setup() {
  Serial.begin(9600);
  while (!Serial);

  dht.begin();

  Serial.println("LoRa SX1278 Sender - Arduino Due");

  // Set LoRa pins
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  // Start LoRa
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // =========================
  // Long-range radio settings
  // =========================
  LoRa.setSpreadingFactor(12);      // Max range
  LoRa.setSignalBandwidth(125E3);   // 125 kHz
  LoRa.setCodingRate4(8);           // 4/8
  LoRa.setTxPower(17);              // Strong TX
  LoRa.enableCrc();                 // Better reliability


  Serial.println("LoRa initialized successfully!");
}

void loop() {
  float humidity = dht.readHumidity();

  // Read temperature in Celsius
  float temperature = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  message = "T:" + String(temperature) + "C H:" + String(humidity) + "% : "+String(counter);


  Serial.print("Sending packet: ");
  Serial.println(message);

  // Begin packet
  LoRa.beginPacket();

  // Packet content
 // LoRa.print("Hello from Due - Packet ");
  LoRa.print(message);

  // End and send packet
  LoRa.endPacket();

  counter++;

  delay(2000); // send every 2 seconds
}