#include <DHT.h>
#include <LiquidCrystal.h>

// Configuración del DHT
#define DHTPIN 53       // Pin digital conectado al sensor
#define DHTTYPE DHT22   // Tipo de sensor DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuración del LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Definimos los valores del botón según el ADC
#define SELECT_BUTTON 720
#define LEFT_BUTTON 480
#define DOWN_BUTTON 320
#define UP_BUTTON 140
#define TOLERANCE 50

// Variables para el menú
int menuIndex = 0;       // Índice del menú principal
bool inSubmenu = false;  // Indica si se está en un submenú

void setup() {
  // Iniciar el sensor DHT y LCD
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();

  // Mostrar el mensaje inicial
  lcd.setCursor(0, 0);
  lcd.print("Bienvenido!");
  delay(2000);
  mostrarMenu();  // Mostrar el menú inicial
}

void loop() {
  // Leer el estado de los botones
  int buttonValue = analogRead(A0);

  if (!inSubmenu) { // Si está en el menú principal
    if (isButtonPressed(buttonValue, UP_BUTTON)) {
      menuIndex = (menuIndex - 1 + 5) % 5; // Ciclar hacia arriba
      mostrarMenu();
    } else if (isButtonPressed(buttonValue, DOWN_BUTTON)) {
      menuIndex = (menuIndex + 1) % 5; // Ciclar hacia abajo
      mostrarMenu();
    } else if (isButtonPressed(buttonValue, SELECT_BUTTON)) {
      seleccionarOpcion(menuIndex); // Seleccionar la opción actual
    }
  } else { // Si está en un submenú
    if (isButtonPressed(buttonValue, LEFT_BUTTON)) {
      inSubmenu = false; // Regresar al menú principal
      mostrarMenu();
    }
  }

  delay(200); // Retardo para evitar rebotes
}

// Función para mostrar el menú principal
void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">");

  switch (menuIndex) {
    case 0:
      lcd.print("Ver Temp");
      break;
    case 1:
      lcd.print("Ver Humedad");
      break;
    case 2:
      lcd.print("Equipo 1");
      lcd.setCursor(0, 1);
      break;
    case 3:
      lcd.print("Equipo 2");
      lcd.setCursor(0, 1);
      break;
    case 4:
      lcd.print("Equipo 3");
      lcd.setCursor(0, 1);
      
      break;
  }
}

// Función para manejar la selección de opciones del menú
void seleccionarOpcion(int opcion) {
  lcd.clear();
  inSubmenu = true;

  switch (opcion) {
    case 0:
      mostrarTemperatura();
      break;
    case 1:
      mostrarHumedad();
      break;
    case 2:
      mostrarMensaje("Josue Luna", "Oscar Carreon");
      break;
    case 3:
      mostrarMensaje("Brayan Garcia", "Wendy Ramirez");
      break;
    case 4:
      mostrarMensaje("Julia Camacho", "Antonio Corpus");
      break;
  }
}

// Función para mostrar la temperatura
void mostrarTemperatura() {
  float t = dht.readTemperature();

  if (isnan(t)) {
    mostrarMensaje("Error", "Sensor");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);
  lcd.print(" C");
}

// Función para mostrar la humedad
void mostrarHumedad() {
  float h = dht.readHumidity();

  if (isnan(h)) {
    mostrarMensaje("Error", "Sensor");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(h, 1);
  lcd.print(" %");
}

// Función para mostrar mensajes genéricos en el LCD
void mostrarMensaje(String linea1, String linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);
  lcd.setCursor(0, 1);
  lcd.print(linea2);
}

// Función para determinar si un botón fue presionado
bool isButtonPressed(int value, int target) {
  return value >= target - TOLERANCE && value <= target + TOLERANCE;
}