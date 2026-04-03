
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =========================
// LCD settings
// Try 0x27 first, if not working try 0x3F
// =========================
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// =========================
// LoRa pin definitions
// =========================
#define SS_PIN    D8   // GPIO15
#define RST_PIN   D0   // GPIO16
#define DIO0_PIN  D3   // GPIO2

#define LORA_FREQUENCY 433E6   // SX1278 usually 433 MHz
int counter =0 ;
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("LoRa + LCD Receiver Starting...");

  // =========================
  // I2C LCD init
  // =========================
  Wire.begin(D2, D1);   // SDA, SCL for NodeMCU
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LoRa Receiver");
  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  // =========================
  // LoRa init
  // =========================
 
 
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LoRa FAILED!");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring");

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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LoRa Ready");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
}

void loop() {
  
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    counter++ ;
    String incoming = "";

    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();

    // =========================
    // Serial output
    // =========================
    Serial.println("--------------------------------");
    Serial.print("Received: ");
    Serial.println(incoming);
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");
    Serial.println("--------------------------------");

    // =========================
    // LCD output
    // =========================
    lcd.clear();

    // First line: Message (trim to 16 chars)
    lcd.setCursor(0, 0);
    if (incoming.length() > 16) {
      lcd.print(incoming.substring(0, 16));
    } else {
      lcd.print(incoming);
    }

    // Second line: RSSI
    lcd.setCursor(0, 1);
    lcd.print("RSSI:");
    lcd.print(rssi);
    lcd.print(" dBm ");
    lcd.print(counter);
  }
  
}