/*
 * TUT Embedded Systems - DHT22 Environmental Monitor
 * Author: Njabulo Msibi | Tshwane University of Technology
 * Date: 20 May 2025
 * Board: Arduino Uno | Sensor: DHT22 | Display: 20x4 I2C LCD
 * 
 * C++ firmware for reading DHT22 temperature/humidity and displaying
 * via I2C LCD1602. Demonstrates sensor drivers and I2C protocol.
 */

#include <Wire.h>                // Arduino I2C/TWI library for LCD communication
#include <LiquidCrystal_I2C.h>   // I2C LCD driver library for 20x4 displays
#include "DHT.h"                 // Adafruit DHT sensor library

const int addr=0x27;             // I2C address of LCD module - run I2C scanner if display blank

 // Hardware pin and sensor configuration
#define DHTPIN 7                 // DHT22 data wire connected to Arduino digital pin 7
#define DHTTYPE DHT22            // Specify sensor type: DHT22/AM2302

// Change 0x27 to your LCD's I2C address if different (e.g. 0x3F)
// Initialize LCD object: (I2C address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 20, 4); 

// Global variables for sensor readings
float hum;                       // Stores humidity percentage
float temp;                      // Stores temperature in Celsius

DHT dht(DHTPIN,DHTTYPE);         // DHT sensor object

void setup() {
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the backlight
  
  lcd.setCursor(16, 2); // Row 0, Column 0 - set cursor to col 16, row 2
  
  dht.begin();         // Initialize DHT sensor
}

void loop() {
  delay(2000);         // 2s refresh rate - DHT22 min sampling period
  
  hum=dht.readHumidity();      // Read humidity from DHT22
  temp =dht.readTemperature(); // Read temperature from DHT22
  
  lcd.clear();         // Clear LCD display
  
  lcd.setCursor(0, 0); // Column 0, Row 0
  lcd.print("Temp: "); // Print temperature label
  lcd.print(temp);     // Print temperature value
  lcd.print(" C");     // Print Celsius unit
  
  lcd.setCursor(0, 1); // Column 0, Row 1
  lcd.print("Humid: "); // Print humidity label
  lcd.print(hum);       // Print humidity value
  lcd.print(" %");      // Print percentage unit
  // No loop logic needed 
}