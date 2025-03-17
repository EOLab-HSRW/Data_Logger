#include <Wire.h>
#include "Adafruit_EEPROM_I2C.h"
#include <SPI.h>
#include <SD.h>

#define EEPROM_ADDR 0x50  // Die I2C-Adresse des EEPROMs
#define MAXADD 262143     // Maximale Adresse im EEPROM (für 256 KB)

// Instanz für das I2C-EEPROM
Adafruit_EEPROM_I2C i2ceeprom;

// Initialisierungsfunktion für das EEPROM
void eeprom_init() {
  // Einschalten der Stromversorgung für das EEPROM
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300); // Warten für 0.3 Sekunden
  Serial.println("Stromversorgung eingeschaltet...");

  // Verbindung zum EEPROM überprüfen
  if (i2ceeprom.begin(EEPROM_ADDR)) {  
    Serial.println("I2C EEPROM gefunden");
  } else {      
    while (1) {
      Serial.println("I2C EEPROM nicht identifiziert ... Überprüfen Sie Ihre Verbindungen?");
      delay(10);
    }     
  }
}

// Funktion zum Lesen von Daten aus dem EEPROM
void readData(unsigned long address, byte *buffer, unsigned int size) {
  i2ceeprom.read(address, buffer, size);
}

// Funktion zum Schreiben auf die SD-Karte
void writeFile(const char *path, const char *message) {
  Serial.printf("Schreibe Datei: %s\n", path);
  File file = SD.open(path, FILE_APPEND);
  if (file) {
    if (file.print(message)) {
      Serial.println("Datei geschrieben.");
    } else {
      Serial.println("Schreiben fehlgeschlagen.");
    }
    file.println();
    file.close();
  } else {
    Serial.println("Öffnen der Datei zum Schreiben fehlgeschlagen.");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) { delay(100); }

  // EEPROM und SD-Karte initialisieren
  eeprom_init();

  if (!SD.begin()) { 
    Serial.println("Initialisierung der SD-Karte fehlgeschlagen!");
    return;
  }
  Serial.println("SD-Karte initialisiert.");

  // Konfiguration des EEPROMs zur Einstellung der Startadresse
  // i2ceeprom.write(2, 1);
  // i2ceeprom.write(3, 4);

  // Daten aus dem EEPROM lesen und auf die SD-Karte schreiben
  byte buffer[32];
  unsigned long addr = 0;
  const unsigned long eepromSize = 100; // Nur 100 Bytes lesen
  unsigned long bytesRead = 0;

  while (bytesRead < eepromSize) {
    unsigned int chunkSize = min((unsigned long)32, eepromSize - bytesRead);
    readData(addr, buffer, chunkSize);
    
    String message = "";
    for (int i = 0; i < chunkSize; i++) {
      message += String(buffer[i], HEX) + " ";
    }
    
    writeFile("/Test.txt", message.c_str());
    
    addr += chunkSize;
    bytesRead += chunkSize;
  }

  Serial.println("Erfolgreich auf die SD-Karte geschrieben.");
}

void loop() {
}
