
#include <SPI.h>
#include <LoRa.h>

// LoRa pin definitions
#define SS_PIN    10
#define RST_PIN    9
#define DIO0_PIN   2

// SX1278 is commonly 433 MHz
#define LORA_FREQUENCY 433E6

void setup() {
  Serial.begin(9600);

  // For Pro Mini this usually doesn't block forever,
  // but it's okay to keep it simple
  delay(1000);
  Serial.println("LoRa SX1278 Receiver - Arduino Pro Mini 3.3V");

  // Set LoRa pins
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  // Start LoRa
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa initialized successfully!");
  Serial.println("Waiting for packets...");
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.println("--------------------------------------------------");
    Serial.print("Packet received (");
    Serial.print(packetSize);
    Serial.println(" bytes)");

    // Read incoming message
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    Serial.print("Message: ");
    Serial.println(incoming);

    Serial.print("RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.println(" dBm");

    Serial.print("SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.println(" dB");

    Serial.println("--------------------------------------------------");
  }
}