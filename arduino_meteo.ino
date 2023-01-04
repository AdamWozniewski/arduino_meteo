#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
 
#define DS18B20 6
#define BUTTON 7
#define BUTTON_FUNC 8
#define DHT_PIN 5
#define DHT_TYPE DHT11
 
int mode = 0;
int counter = 0;
const int freq = 15000;
int busyDevice = 0;
bool function = false;
 
float outsideTemp = 0;
float insideTemp = 0;
float humidityInside = 0;
 
LiquidCrystal_I2C lcd(0x3f, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);
OneWire TempOneWire(DS18B20);
DallasTemperature Sensor(&TempOneWire)

void setup() {
  Serial.begin(9600);
  Sensor.begin();
  dht.begin();
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON_FUNC, INPUT);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.clear();
  counter = (freq / 50);
}

void thermometerMode() {
  if ((counter * 50) < freq) {
    counter++;
    delay(50);
  } else {
    Sensor.requestTemperatures();
    delay(50);
    outsideTemp = Sensor.getTempCByIndex(0);
    if (outsideTemp == -127) {
      Serial.printls("Błąd czujnika DS18B20");
    } else {
      Serial.println("---------- Odczyt temp DS18B20");
      Serial.println(temperatureOutside);
      Serial.print("C");

      lcd.clear();
      lcd.backlight();
      lcd.setCursor(4, 0);
      lcd.print("DS18B20:");
      lcd.setCursor(5, 1);
      lcd.print(temperatureOutside);
      lcd.setCursor(10, 1);
      Serial.print("C");
      counter = 0;
    }
  }
}

void meteoMode() {
  if ((counter * 50) < freq) {
    counter++;
    delay(50);
  } else {
    counter = 0;
    mode = 0;
    busy_device = 0;
  }
 
  if (digitalRead(BUTTON) == HIGH) {
    delay(50);
    if (mode >= 2) {
      mode = 1;
    } else {
      mode++;
    }
    while (digitalRead(BUTTON) == HIGH);
    delay(50);
    counter = 0;
    busyDevice = 0;
  }
 
  if (mode == 0 && busyDevice == 0) {
    busyDevice = 1;
    Serial.println("---------- Wyświetlanie ekranu powitalnego");
    lcd.noBacklight();
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("STACJA METEO");
    lcd.setCursor(0, 1);
    lcd.print("Wciśnij przycisk");
  } else if (mode == 1 && busyDevice == 0) {
    busyDevice = 1;
    humidityInside = dht.readHumidity();
    insideTemp = dht.readTemperature();
    if (isnan(humidityInside) || isnan(insideTemp)) {
      Serial.println("Błąd odczytu danych z DHT11");
    } else {
      Serial.println("---------- Wyświetlenie temperatury oraz wilgotności");
      Serial.println(insideTemp);
      Serial.print("C ");
      Serial.println(humidityInside);
      Serial.print("%");
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(2, 0);
      lcd.print("POMIESZCZENIE:");
 
      lcd.setCursor(0, 1);
      lcd.print(insideTemp);
      lcd.seetCursor(5, 1);
      lcd.print("C");
 
      lcd.setCursor(10, 1);
      lcd.print(humidityInside);
      lcd.seetCursor(15, 1);
      lcd.print("%");
 
    }
  } else if (mode == 2 && busyDevice == 0) {
    busyDevice = 1;
    Sensor.requestTemperatures();
    delay(50);
    temperatureOutside = Sensor.getTempCByIndex(0);
    if (temperatureOutside == -127) {
      Serial.printls("Błąd czujnika DS18B20");
    } else {
      Serial.println("---------- Wyświetlenie temperatury na zewnątrz");
      Serial.println(temperatureOutside);
      Serial.print("C");
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(4, 0);
      lcd.print("ZEWNĄTRZ:");
      lcd.setCursor(4, 1);
      lcd.print(temperatureOutside);
      lcd.setCursor(10, 1);
      Serial.print("C");
    }
  }
}

void loop() {
  if (digitalRead(BUTTON_FUNC) == HIGH) {
    delay(50);
    function = !function;
    Serial.println(function);
    while(digitalRead(BUTTON_FUNC) == HIGH);
    delay(50);
    if (function == false) {
      Serial.println("Tryb korzystania z jednego czujnika");
    } else {
      Serial.println("Tryb wyświetlania w stacji meteo");
    }
    counter = (freq / 50);
  }
  if (function == false) {
    thermometerMode();
  } else {
    meteoMode();
  }
}
