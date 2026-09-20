# Projektarchiv – Victron ESP32 Display

## Stand
Version: **V4.2.0**  
Entwickler: **Ebner Stephan**  
Lizenz: **MIT**

## Zweck
Standalone-Touchdisplay für Victron Cerbo GX. Ein ESP32 E32R28T empfängt lokale MQTT-Daten und stellt sie auf einem ILI9341-TFT dar. Konfiguration erfolgt über Touch und einen integrierten Webserver.

## Hardware
ESP32-WROOM-32E / E32R28T, 2,8 Zoll ILI9341 240×320, resistiver Touch. TFT läuft über HSPI, Touch über VSPI.

## Software
Arduino ESP32 Core 3.2.0. Wesentliche Bibliotheken: Adafruit GFX, Adafruit ILI9341, PubSubClient, ArduinoJson. Einstellungen werden mit Preferences/NVS persistent gespeichert.

## Anzeige
Sechs konfigurierbare HOME-Kacheln, MQTT-Scanner, Zahlen-/Balken-/Sparkline-Darstellung und Trendseite. HOME-Titel ist frei konfigurierbar.

## Webinterface
Konfiguration unter der IP-Adresse des ESP32. API-Endpunkte umfassen /api/config, /api/status und /api/save. /health dient der Diagnose. Firmware kann zusätzlich über den vorhandenen Web-OTA-Endpunkt hochgeladen werden.

## OTA
Arduino OTA verwendet einen eigenen Hostnamen und optional ein eigenes OTA-Passwort. MQTT-Passwort wird nicht als OTA-Passwort verwendet.

## GitHub Update V4.2.0
Repository: stephanflug/Victron-ESP32-Display. Die Firmware kann die öffentliche Manifestdatei firmware/latest.json prüfen. Eine höhere Version wird im Webinterface gemeldet. Die Installation erfolgt bewusst erst nach Anwenderaktion. Das Manifest verweist bei veröffentlichter OTA-Firmware auf eine kompilierte .bin.

## Sicherheit
Keine Zugangsdaten im Repository ablegen. Passwörter nicht über Konfigurations-APIs ausgeben. Für öffentliche GitHub-Updates ist kein GitHub-Token im ESP32 erforderlich.

## Historie
V3 führte konfigurierbare Kacheln und Trends ein. V3.3 ergänzte OTA. V4 führte den Web-Konfigurator ein. V4.1 verbesserte Performance, Speicherung, OTA-Trennung, Webserver-Stabilität und die Bildschirmtastatur. V4.1.7 ergänzte den frei konfigurierbaren HOME-Titel. V4.2.0 ergänzt Entwicklerangabe und GitHub-basierte Updateprüfung.
