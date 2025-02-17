#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 53 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8,9,4,5,6,7);  

void setup() {
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity(); 
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %\t");
  lcd.setCursor(0, 1);  
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C ");
}
