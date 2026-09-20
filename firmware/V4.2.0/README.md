# Firmware V4.2.0

**Entwickler:** Ebner Stephan

Dieser Ordner enthält den Arduino-Quellcode der Version V4.2.0.

## Dateien
- `Victron_Cerbo_Display_E32R28T_V4_2_0.ino` – Hauptfirmware
- `webui.h` – integrierter Web-Konfigurator

## Updatefunktion
V4.2.0 prüft das öffentliche Manifest `../latest.json`. Eine neue Firmware wird nur nach ausdrücklicher Anwenderaktion installiert.

> Hinweis: Für GitHub-OTA muss eine kompilierte `.bin` als Release-Datei veröffentlicht und anschließend in `latest.json` eingetragen werden.
