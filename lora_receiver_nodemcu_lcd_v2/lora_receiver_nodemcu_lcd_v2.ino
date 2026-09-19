
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

#define LORA_FREQ 433E6


unsigned long packetCount = 0;
unsigned long errorCount = 0;
unsigned long lastStatusTime = 0;

unsigned long statusInterval = 10000;


//===============
//lcd helper function
//==================





void setup() {


}


void loop() {

}