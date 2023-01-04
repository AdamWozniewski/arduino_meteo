# Stacja Pogodowa

Stacja Meteo oparta o **Arduino Nano** z wykorzystaniem:
* Ekran LCD 16px
* DS18b20
* DHT11

Posiada dwa tryby pracy. Pierwszy, który sprawdza temperaturę na zewnątrz oraz drugi, który odświeża się co 15 sekund i podaje aktualizowane dane zarówno z zewnątrz jak i w środku pomieszczenia.
Sprawdzana jest temperatura w stopniach Celsjusza, oraz wilgotność powietrza w %.
---
Wykorzystane technologie:
* C++
* Arduino IDE
* FRITZING
---

Połączenia:

* Przycisk 1 - **PIN_7**
* Przycisk 2 - **PIN_8**
* Czujnik DS18B20 - **PIN_6**
* Czujnik DHT11 - **PIN_5**
---
* Przyciski posiadają rezystory ściagające 10KOhm
* I2C LCD posiada zwarte podświetlenie (najlepiej skorzystać z ekranem z wbudowanym konwerterem)
* DS18B20 posiada rezystor 4K7Ohm podłaczony od nóżki zasilającej do szyny danych
* SDA ekranu do A4 
* SCL ekranu do A5