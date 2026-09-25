# ioBroker → MQTT Bridge

Dieses Zusatzscript exportiert ausgewählte ioBroker-State-Bereiche auf einen MQTT-Broker.

## Exportierte Bereiche

- `0_userdata.*`
- `goodwe_we.*`
- `hm-rega.*`
- `hm-rpc.*`

Beim Start des Scripts werden alle aktuell vorhandenen Werte übertragen. Anschließend wird jede Änderung automatisch publiziert.

## MQTT-Topic

Die ioBroker-ID wird in ein MQTT-Topic umgewandelt.

Beispiel:

```text
hm-rpc.0.ABC123.1.TEMPERATURE
```

wird zu:

```text
iobroker/hm-rpc/0/ABC123/1/TEMPERATURE
```

Die Payload enthält den aktuellen Wert des ioBroker-States.

## Installation

1. In ioBroker den JavaScript-Adapter öffnen.
2. Ein neues JavaScript anlegen.
3. Den Inhalt von `iobroker-mqtt-bridge.js` einfügen.
4. Bei Bedarf `MQTT_INSTANCE` anpassen. Standard ist `mqtt.0`.
5. Script starten.

Der verwendete MQTT-Adapter muss mit dem gewünschten MQTT-Broker verbunden sein.

## Einstellungen

Im Script können unter anderem angepasst werden:

```javascript
const MQTT_INSTANCE = 'mqtt.0';
const MQTT_PREFIX = 'iobroker';
const RETAIN = true;
const PUBLISH_ON_START = true;
```

Mit `RETAIN = true` erhält ein neu verbundener MQTT-Client direkt den zuletzt veröffentlichten Wert eines Topics.

## ESP32 Display

Im Standard-MQTT-Modus des Victron ESP32 Displays kann anschließend beispielsweise auf

```text
iobroker/#
```

abonniert werden. Damit stehen die von ioBroker exportierten Werte auch für frei konfigurierbare MQTT-Kacheln zur Verfügung.
