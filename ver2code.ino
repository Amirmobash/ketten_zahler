/*
 * Besucherzähler mit OLED-Display und Relais
 * Autor: AmirMobasheraghdam
 * Datum: 2025
 * 
 * Dieses Projekt zählt Personen, die einen Raum betreten oder verlassen,
 * und schaltet bei Anwesenheit ein Licht (Relais) ein.
 * Die Anzeige erfolgt auf einem OLED-Display (SSD1306).
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED-Breite in Pixeln
#define SCREEN_HEIGHT 64    // OLED-Höhe in Pixeln
#define OLED_RESET -1       // Reset-Pin (-1 wenn mit Arduino-Reset verbunden)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define inSensor 2   // Sensor für Eintritt
#define outSensor 3  // Sensor für Austritt

int inStatus;
int outStatus;

int countin = 0;   // Zähler für Eintritte
int countout = 0;  // Zähler für Austritte

int in;   // alter Wert für Eintritte (vor der Erhöhung)
int out;  // alter Wert für Austritte (vor der Erhöhung)
int now;  // aktuelle Anzahl anwesender Personen

#define relay 5    // Relais-Pin (Lichtsteuerung)

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialisierung mit I2C-Adresse 0x3C (128x64)
  delay(2000);
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);  // Relais aus (Licht aus)

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.print("Besucher");
  display.setCursor(20, 40);
  display.print("zähler");
  display.display();
  delay(3000);
}

void loop()
{
  inStatus  = digitalRead(inSensor);
  outStatus = digitalRead(outSensor);

  if (inStatus == 0)   // Wenn Eintrittssensor auslöst (LOW)
  {
    in = countin++;    // alten Wert merken und Zähler erhöhen
  }

  if (outStatus == 0)  // Wenn Austrittssensor auslöst (LOW)
  {
    out = countout++;  // alten Wert merken und Zähler erhöhen
  }

  now = in - out;      // aktuelle Anzahl = Eintritte - Austritte

  if (now <= 0)
  {
    digitalWrite(relay, HIGH);   // Licht aus
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 15);
    display.print("Kein Besucher");
    display.setCursor(5, 40);
    display.print("Licht Aus");
    display.display();
    delay(500);
  }
  else
  {
    digitalWrite(relay, LOW);    // Licht ein

    display.clearDisplay();
    display.setTextColor(WHITE);

    display.setTextSize(1);
    display.setCursor(15, 0);
    display.print("Aktuelle Besucher");
    display.setTextSize(2);
    display.setCursor(50, 15);
    display.print(now);

    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("REIN: ");
    display.print(in);

    display.setTextSize(1);
    display.setCursor(70, 40);
    display.print("RAUS: ");
    display.print(out);

    display.display();
    delay(500);
  }
}
