
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//=======================
//== LCD==================
//=========================

#define LCD_ADDRESS 0x3F
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS,LCD_COLS,LCD_ROWS);  

//================
//====Lora Module =======
//===================

#define SS_PIN D8 //GPIO15
#define RST_PIN D0 //GPIO16
#define DIO0_PIN D3 //GPIO0/2
#define LED_PIN D4

#define LORA_FREQ 433E6


unsigned long packetCount = 0;
unsigned long errorCount = 0;
unsigned long lastStatusTime = 0;

unsigned long statusInterval = 10000;


//===============
//lcd helper function
//==================

void lcdMessage(const char* line1, const char* line2){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void lcdMessage(String line1,String line2){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1.substring(0,16));
  lcd.setCursor(0,1);
  lcd.print(line2.substring(0,16));

}

//==================
// Lora Initialization
//====================

bool initializeLora(){
  Serial.println("Initializing Lora");
  LoRa.setPins(SS_PIN,RST_PIN,DIO0_PIN);
  
  if(!LoRa.begin(LORA_FREQ)){
    errorCount++ ;
    Serial.println("LoRa failed to start");
    lcdMessage("Lora Error","Check Wiring");
    return false;
  }

    // -----------------------------------------------
  // Radio settings
  // These MUST match the transmitter
  // -----------------------------------------------

  
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(8);
  LoRa.setTxPower(17);
  
  LoRa.enableCrc();
 
  Serial.println("LoRa started successfully");
  lcdMessage("Lora OK","Waiting");
  
  return true;
}



//============================
// Receive packet
//==============================

void receivePacket(){
  long packetSize = LoRa.parsePacket() ;
  
  if (packetSize <=0){
    Serial.println ("Didn't receive any packets") ;
    return;
  }

  packetCount++ ;
  Serial.println("==========================") ;
  Serial.print("packetCount = ");
  Serial.println(packetCount);
  Serial.print("packetSize = ");
  Serial.println(packetSize);
  Serial.println("bytes ====================");

  String incoming = "" ;
  while (LoRa.available()> 0)
  {
    incoming += (char)LoRa.read() ;
  }


  if (incoming.length() ==0)
  {
    Serial.println("empty incoming packet");
    errorCount++ ;
    lcdMessage("Packet Error","empty packet");
    return;
  }

  Serial.println("Incoming packet================");
  Serial.println(incoming.substring(0,16));

  int rss = LoRa.packetRssi() ;
  Serial.println("Rss ====");
  Serial.print(rss );
  Serial.println("db");
  Serial.println("=============================");
  lcdMessage(incoming.substring(0,16),String(rss)+" "+String(packetCount)) ;
  led_blink();
}


void checkLora(){

  if (millis() - lastStatusTime < 300000) // recreate after 5 mins
  {
    return;
  }
  lastStatusTime = millis();
  if (LoRa.begin(LORA_FREQ))
  {
    Serial.println("connection recreated");
    lcdMessage("LORA recreated",String(packetCount));
  }
  else
  {
    Serial.println("connection couldn't be recreated");
    lcdMessage("Lora Not-recreated",String(packetCount));
  }

}

void led_blink(){
digitalWrite(LED_PIN, HIGH);
delay(500);
digitalWrite(LED_PIN,LOW);

}



void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);

  Serial.println("LoRa Lcd starting");
  Wire.begin(D2,D1);
  lcd.init();
  lcd.backlight();
  lcdMessage("Lora Lcd","starting");

  bool loraOk = initializeLora();
  if(!loraOk) {
    Serial.println("lora initialization failed");
  }
  delay(1000);

}


void loop() {

  receivePacket();
  //checkLora();

  delay(5);
  
}