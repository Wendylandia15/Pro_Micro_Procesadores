#include <LiquidCrystal.h>
#include <DHT.h>
//Temperatura y Humedad 
//Garcia Mayorga Brayan J._ _Ramirez Vazquez Wendy I. 
// Pines del LCD conectados al Arduino: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Definimos el pin digital donde se conecta el sensor DHT
#define DHTPIN 2

// Tipo de sensor (DHT11 en este caso)
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializar el LCD
  lcd.begin(16, 2);

  // Comenzamos el sensor DHT
  dht.begin();

  // Mensaje inicial en el LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp:     C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad:  %");
}

void loop() {
  // Leer datos del sensor
  float t = dht.readTemperature(); // Temperatura en grados Celsius
  float h = dht.readHumidity();    // Humedad relativa en %

  // Validar datos del sensor
  if (isnan(t) || isnan(h)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error sensor");
    delay(2000);
    return;
  }

  // Mostrar temperatura en el LCD
  lcd.setCursor(6, 0); // Ubicación para la temperatura
  lcd.print(t, 1);     // Temperatura con 1 decimal

  // Mostrar humedad en el LCD
  lcd.setCursor(9, 1); // Ubicación para la humedad
  lcd.print(h, 1);     // Humedad con 1 decimal

  // Esperar 2 segundos antes de la siguiente lectura
  delay(2000);
}
