# Victron ESP32 Display

Ein lokales Touchdisplay für **Victron Cerbo GX** auf Basis des **ESP32 E32R28T** mit ILI9341-TFT und resistivem Touch.

**Entwickler:** Ebner Stephan  
**Firmware:** V4.2.0  
**Lizenz:** MIT

## Überblick

Das Projekt stellt wichtige Victron-Livedaten direkt auf einem kompakten ESP32-Touchdisplay dar. Die Daten werden lokal per MQTT vom Cerbo GX empfangen. Die Anzeige und die sechs HOME-Kacheln können direkt am Display oder komfortabel über den integrierten Web-Konfigurator eingerichtet werden.

### Funktionen

- 6 frei konfigurierbare HOME-Kacheln
- lokale Victron-MQTT-Daten
- Batterie-SOC, Spannung, PV-Leistung, Verbrauch, Netzleistung usw.
- Zahlen-, Balken- und Sparkline-Anzeige
- Trendseite mit 10 min / 1 h / 6 h / 24 h
- Touch-Bedienung
- Web-Konfigurator
- frei wählbarer HOME-Titel
- Arduino OTA
- Firmware-Upload über Browser
- GitHub-Updateprüfung ab V4.2.0
- persistente Einstellungen in ESP32 Preferences/NVS

## Hardware

Zielhardware: **ESP32E_2.8inch / E32R28T**, ESP32-WROOM-32E, ILI9341 240×320, resistiver Touch.

| Funktion | GPIO |
|---|---:|
| TFT CS | 15 |
| TFT DC/RS | 2 |
| TFT SCK | 14 |
| TFT MOSI | 13 |
| TFT MISO | 12 |
| Backlight | 21 |
| Touch SCK | 25 |
| Touch MOSI | 32 |
| Touch MISO | 39 |
| Touch CS | 33 |
| Touch IRQ | 36 |

## Installation

1. Den Ordner `firmware/V4.2.0` herunterladen.
2. `.ino` und `webui.h` müssen im selben Arduino-Sketchordner liegen.
3. ESP32 Arduino Core 3.2.0 sowie die benötigten Bibliotheken installieren.
4. Ein OTA-fähiges Partitionsschema auswählen.
5. Firmware zunächst per USB aufspielen.
6. WLAN und Cerbo-GX-MQTT konfigurieren.
7. Danach den Web-Konfigurator über die IP-Adresse des Displays öffnen.

Benötigte Bibliotheken: Adafruit GFX, Adafruit ILI9341, PubSubClient und ArduinoJson.

## Web-Konfigurator

Im Browser:

`http://<IP-DES-DISPLAYS>/`

Dort können HOME-Titel, MQTT-Topics, Bezeichnungen, Einheiten, Nachkommastellen, Darstellungsarten, Display-Timeout und OTA-Einstellungen geändert werden.

Diagnose:

`http://<IP-DES-DISPLAYS>/health`

## Firmwareupdates über GitHub

Ab V4.2.0 kann das Display die Datei `firmware/latest.json` dieses Repositorys prüfen. Ist dort eine höhere Version hinterlegt, wird im Webinterface ein verfügbares Update angezeigt.

Für die Installation muss `firmware_url` auf eine **kompilierte ESP32-.bin-Datei** zeigen. Arduino-`.ino`-Quellcode kann nicht direkt als OTA-Firmware installiert werden.

Die eigentliche Installation eines Updates wird vom Anwender ausgelöst. Es wird nicht ungefragt automatisch installiert.

## Konfiguration und Passwörter

WLAN-, MQTT- und OTA-Passwörter gehören **nicht** in dieses Repository. MQTT- und OTA-Passwort sollten getrennt verwendet werden. Passwörter werden von der Konfigurations-API nicht zurückgegeben.

## Projektstruktur

```text
Victron-ESP32-Display/
├── README.md
├── LICENSE
├── PROJECT.md
└── firmware/
    ├── latest.json
    └── V4.2.0/
        ├── Victron_Cerbo_Display_E32R28T_V4_2_0.ino
        └── webui.h
```

## Lizenz

Dieses Projekt steht unter der **MIT License**. Weitere Informationen stehen in der Datei `LICENSE`.

## ☕ Unterstütze das Büro-Kaffeekonto!

Damit der Kaffee im Büro nie ausgeht und die Entwicklung weiter auf Hochtouren läuft, freuen wir uns über eine kleine Unterstützung. ☕💻

Jeder Beitrag hilft dabei, die Kaffeemaschine am Laufen zu halten und sorgt für genügend Energie für neue Ideen, Funktionen und Updates.

[![PayPal – Kaffee spendieren](https://img.shields.io/badge/PayPal-Kaffee%20spendieren-0070BA?logo=paypal&logoColor=white)](https://paypal.me/stephanflug)

**☕ [Kaffee via PayPal spendieren](https://paypal.me/stephanflug)**

Vielen Dank für deine Unterstützung! ❤️
