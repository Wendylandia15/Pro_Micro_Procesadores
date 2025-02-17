#include <DHT.h>
#include <LiquidCrystal.h>
// Configuración del DHT
#define DHTPIN 53       // Pin digital conectado al sensor
#define DHTTYPE DHT22   // Tipo de sensor DHT22
DHT dht(DHTPIN, DHTTYPE);
// Configuración del LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Definimos los valores del botón según el ADC
#define SELECT_BUTTON 720  // Valor aproximado del botón Select
#define LEFT_BUTTON 480  // Valor aproximado del botón Left
#define RIGHT_BUTTON 5  // Valor aproximado del botón Left
#define DOWN_BUTTON 320 // Valor aproximado del botón Left
#define UP_BUTTON 140 // Valor aproximado del botón Left
#define TOLERANCE 50     // Tolerancia para lectura analógica

void setup() {
  // Iniciamos el sensor DHT
  dht.begin();
  // Iniciamos el LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
}

void loop() {
  // Leer el estado de los botones
  int buttonValue = analogRead(A0);
  // Comprobar si se presionó el botón Select
  if (isButtonPressed(buttonValue, SELECT_BUTTON)) {
    mostrarTemperatura();
  }
  // Comprobar si se presionó el botón Left
  else if (isButtonPressed(buttonValue, LEFT_BUTTON)) {
    E1();
  }
  else if (isButtonPressed(buttonValue, RIGHT_BUTTON)) {
    E2();
  }
  else if (isButtonPressed(buttonValue, UP_BUTTON)) {
    BD();
  }
  else if (isButtonPressed(buttonValue, DOWN_BUTTON)) {
    E3();
  }
  delay(200); // Pequeño retardo para evitar lecturas inestables
}

// Función para mostrar la temperatura en el LCD
void mostrarTemperatura() {
  float t = dht.readTemperature(); // Leer temperatura
  float h = dht.readHumidity();    // Leer humedad
  // Validar las lecturas
  if (isnan(t) || isnan(h)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error sensor");
    return;
  }
  // Mostrar la temperatura y humedad
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1); // Mostrar temperatura con 1 decimal
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(h, 1); // Mostrar humedad con 1 decimal
  lcd.print(" %");
}

// Función para mostrar un texto de ejemplo en el LCD
void E1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Josue Luna");
  lcd.setCursor(0, 1);
  lcd.print("Oscar Carreon");
}

void BD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bienvenido");
  lcd.setCursor(0, 1);
  lcd.print("Dragon@!");
}

void E2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Brayan Garcia");
  lcd.setCursor(0, 1);
  lcd.print("Wendy Ramirez");
}

void E3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Julia Camacho");
  lcd.setCursor(0, 1);
  lcd.print("Antonio Corpus");
}

// Función para determinar si un botón fue presionado
bool isButtonPressed(int value, int target) {
  return value >= target - TOLERANCE && value <= target + TOLERANCE;
}
