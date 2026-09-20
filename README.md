# Victron ESP32 Display

Ein lokales Touchdisplay für **Victron Cerbo GX** auf Basis des **ESP32 E32R28T** mit ILI9341-TFT und resistivem Touch.

[![Release](https://img.shields.io/github/v/release/stephanflug/Victron-ESP32-Display?display_name=release&label=Version)](https://github.com/stephanflug/Victron-ESP32-Display/releases/latest)
[![License](https://img.shields.io/github/license/stephanflug/Victron-ESP32-Display)](LICENSE)

**Entwickler:** Ebner Stephan  
**Aktuelle Firmware:** V4.2.0  
**Lizenz:** MIT

## Download

Für normale Anwender wird die jeweils veröffentlichte Version über **GitHub Releases** bereitgestellt.

**➡️ [Aktuelle Releases und Downloads](https://github.com/stephanflug/Victron-ESP32-Display/releases)**

Für V4.2.0 steht das komplette Projekt als:

`Victron_Cerbo_Display_E32R28T_V4_2_0.zip`

im Release zur Verfügung.

**➡️ [Release V4.2.0 öffnen](https://github.com/stephanflug/Victron-ESP32-Display/releases/tag/4.2.0)**

> Das ZIP enthält das komplette Projekt für Arduino IDE. Eine separat veröffentlichte `.bin` wird für direkte OTA-/GitHub-Firmwareupdates des ESP32 verwendet.

## Überblick

Das Projekt stellt wichtige Victron-Livedaten direkt auf einem kompakten ESP32-Touchdisplay dar. Die Daten werden lokal per MQTT vom Cerbo GX empfangen. Die Anzeige und die sechs HOME-Kacheln können direkt am Display oder komfortabel über den integrierten Web-Konfigurator eingerichtet werden.

### Funktionen

- 6 frei konfigurierbare HOME-Kacheln
- lokale Kommunikation mit Victron Cerbo GX über MQTT
- Batterie-SOC, Spannung, PV-Leistung, Verbrauch, Netzleistung und frei wählbare MQTT-Werte
- Zahlen-, Balken- und Sparkline-Darstellung
- Trendanzeige für 10 Minuten, 1 Stunde, 6 Stunden und 24 Stunden
- Touch-Bedienung
- integrierter Web-Konfigurator
- frei wählbarer HOME-Titel
- Arduino OTA
- manueller Firmware-Upload über den Browser
- GitHub-Updateprüfung ab V4.2.0
- persistente Einstellungen über ESP32 Preferences/NVS

## Hardware

Zielhardware: **ESP32E_2.8inch / E32R28T** mit ESP32-WROOM-32E, ILI9341 240×320 und resistivem Touch.

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

## Erstinstallation

1. Unter **Releases** die gewünschte Version herunterladen.
2. Das ZIP auf dem PC entpacken.
3. `.ino` und `webui.h` müssen sich im selben Arduino-Sketchordner befinden.
4. In der Arduino IDE den **ESP32 Arduino Core 3.2.0** installieren.
5. Benötigte Bibliotheken installieren: **Adafruit GFX Library**, **Adafruit ILI9341**, **PubSubClient** und **ArduinoJson**.
6. Das passende ESP32-Board sowie ein **OTA-fähiges Partitionsschema** auswählen.
7. Die Firmware zunächst per USB auf den ESP32 übertragen.
8. WLAN und die MQTT-Verbindung zum Cerbo GX konfigurieren.
9. Anschließend kann der Web-Konfigurator über die IP-Adresse des Displays aufgerufen werden.

## Web-Konfigurator

Nach erfolgreicher WLAN-Verbindung im Browser öffnen:

`http://<IP-DES-DISPLAYS>/`

Über die Weboberfläche können unter anderem HOME-Titel, MQTT-Topics, Bezeichnungen, Einheiten, Nachkommastellen, Darstellungsarten, Display-Timeout und OTA-Einstellungen geändert werden.

Für einen einfachen Webserver-Test steht zur Verfügung:

`http://<IP-DES-DISPLAYS>/health`

## Firmwareupdates über GitHub Releases

Ab **V4.2.0** ist die Infrastruktur für GitHub-basierte Firmwareupdates vorgesehen.

Das Display prüft die öffentliche Datei:

`firmware/latest.json`

Darin stehen die aktuelle Version, Hinweise zur Version und die Downloadadresse der kompilierten Firmware.

### ZIP und BIN – was ist der Unterschied?

**ZIP:** Das vollständige Projekt für Anwender und Entwickler. Es enthält Arduino-Quellcode, Webinterface und weitere Projektdateien.

**BIN:** Die bereits kompilierte ESP32-Firmware. Nur diese Datei kann vom ESP32 direkt als Firmwareupdate installiert werden.

Ein ZIP-Archiv kann deshalb **nicht direkt als OTA-Firmware** auf den ESP32 geschrieben werden.

### Ablauf eines automatischen Updates

1. Das Display prüft `latest.json`.
2. Installierte und veröffentlichte Version werden verglichen.
3. Bei einer neueren Version erscheint im Webinterface **„Update verfügbar“**.
4. Der Anwender startet das Update ausdrücklich über **„Update installieren“**.
5. Der ESP32 lädt die veröffentlichte `.bin`.
6. Die Firmware wird installiert.
7. Der ESP32 startet neu.

Ein Update wird **nicht ungefragt automatisch installiert**.

### Neue Version veröffentlichen

Für zukünftige Versionen, zum Beispiel V4.2.1:

1. GitHub → **Releases** → **Draft a new release**.
2. Tag beispielsweise `4.2.1` anlegen.
3. Release-Titel `V4.2.1` eintragen.
4. Komplettes Projekt-ZIP hochladen, z. B. `Victron_Cerbo_Display_E32R28T_V4_2_1.zip`.
5. Für ESP32-OTA zusätzlich die kompilierte Firmware hochladen, z. B. `Victron_Cerbo_Display_E32R28T_V4_2_1.bin`.
6. Änderungen der Version in den Release Notes beschreiben.
7. **Publish release** auswählen.
8. `firmware/latest.json` auf die neue Version und die neue BIN-Datei aktualisieren.

## Einstellungen bei einem Update

Die Konfiguration wird in **ESP32 Preferences/NVS** gespeichert. Bei einem normalen Firmwareupdate bleiben diese Einstellungen erhalten, solange die Firmware den NVS-Bereich nicht ausdrücklich löscht oder inkompatibel verändert.

## Sicherheit

WLAN-, MQTT-, OTA- oder andere Zugangsdaten dürfen **nicht in GitHub veröffentlicht** werden.

- keine WLAN-Passwörter im Repository
- keine MQTT-Passwörter im Repository
- kein GitHub-Token in der Firmware
- separates OTA-Passwort verwenden
- Konfigurations-API gibt gespeicherte Passwörter nicht zurück

Da das Repository öffentlich ist, kann die Updateprüfung ohne fest eingebauten GitHub-Token erfolgen.

## Projektstruktur

```text
Victron-ESP32-Display/
├── .github/
│   └── workflows/
│       └── build-firmware.yml
├── README.md
├── LICENSE
├── PROJECT.md
└── firmware/
    ├── latest.json
    └── V4.2.0/
        ├── Victron_Cerbo_Display_E32R28T_V4_2_0.ino
        ├── webui.h
        └── README.md
```

## Lizenz

Dieses Projekt steht unter der **MIT License**. Siehe [LICENSE](LICENSE).

## ☕ Unterstütze das Büro-Kaffeekonto!

Damit der Kaffee im Büro nie ausgeht und die Entwicklung weiter auf Hochtouren läuft, freuen wir uns über eine kleine Unterstützung. ☕💻

Jeder Beitrag hilft dabei, die Kaffeemaschine am Laufen zu halten und sorgt für genügend Energie für neue Ideen, Funktionen und Updates.

[![PayPal – Kaffee spendieren](https://img.shields.io/badge/PayPal-Kaffee%20spendieren-0070BA?logo=paypal&logoColor=white)](https://paypal.me/stephanflug)

**☕ [Kaffee via PayPal spendieren](https://paypal.me/stephanflug)**

Vielen Dank für deine Unterstützung! ❤️
