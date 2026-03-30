#include <SPI.h>
#include <LoRa.h>

// LoRa control pins
#define SS_PIN   10
#define RST_PIN   9
#define DIO0_PIN  2

// SX1278 usually works at 433E6
#define LORA_FREQUENCY 433E6

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa SX1278 Sender - Arduino Due");

  // Set LoRa pins
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  // Start LoRa
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa initialized successfully!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Begin packet
  LoRa.beginPacket();

  // Packet content
  LoRa.print("Hello from Due - Packet ");
  LoRa.print(counter);

  // End and send packet
  LoRa.endPacket();

  counter++;

  delay(2000); // send every 2 seconds
}