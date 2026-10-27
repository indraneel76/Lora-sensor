# Remote Weather Sensor

## Project Description

The project is about sending humidity /temperature over radio (Long range frequency). It has two components namely a trasmitter and receiver.

This has two arduino project
- Lora_receiver_nodemcu
- Lora_sender_arduino_due

**lora_receiver_nodemcu** has the code for receving the temperature and humidity data using LORA (long range) from the transmitter. This run on nodemcu ESP8266 and has to be opened in arduino IDE with mode selected as nodemcu

**lora_sender_arduino_due** has the code for sending temperature and humidity over LORA(long range) capture from temperature /humidty sensor DHT11. This runs on Arduino Due and has to be open in arduino IDE with Arduino Due as the board.

## Ingredients / Component needed
 - Node MCU ESP8266
 - Mini breadboard - 2
 - 16x2 LCD display with I²C
 - DHT11Sensor module
 - Lora Module 2-Pack for Wireless
 - Male-Female jumper wires
 - LED 
 - Arduino Due



## Connection diagram
You need fritzing to see the diagram [Fritzing](https://fritzing.org/)
 - Sender connection diagram : Lora_sender_nodemcu.fzz 
- Receiver connection diagram: Lora_sender_Arduinodue.fzz

