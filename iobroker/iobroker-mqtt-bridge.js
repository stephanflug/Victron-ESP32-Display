/*
 * ioBroker -> MQTT Bridge
 *
 * Exportiert alle State-Werte aus:
 *   - 0_userdata.*
 *   - goodwe_we.*
 *   - hm-rega.*
 *   - hm-rpc.*
 *
 * Beispiel:
 *   hm-rpc.0.ABC123.1.TEMPERATURE
 *   -> iobroker/hm-rpc/0/ABC123/1/TEMPERATURE
 *
 * Voraussetzungen:
 *   - ioBroker JavaScript-Adapter
 *   - ioBroker MQTT-Adapter, z. B. mqtt.0
 *
 * Verhalten:
 *   - sendet beim Start alle aktuell vorhandenen Werte
 *   - sendet danach jede Wertänderung
 *   - MQTT retain ist standardmäßig aktiviert
 */

const MQTT_INSTANCE = 'mqtt.0';
const MQTT_PREFIX = 'iobroker';
const RETAIN = true;
const PUBLISH_ON_START = true;
const INITIAL_SEND_DELAY_MS = 3;

const ROOTS = [
    '0_userdata',
    'goodwe_we',
    'hm-rega',
    'hm-rpc'
];

function isAllowedId(id) {
    return ROOTS.some(root => id.startsWith(root + '.'));
}

function stateIdToTopic(id) {
    const prefix = MQTT_PREFIX.replace(/^\/+|\/+$/g, '');
    return (prefix ? prefix + '/' : '') + id.replace(/\./g, '/');
}

function valueToPayload(value) {
    if (value === undefined) return null;
    if (value === null) return '';

    if (typeof value === 'object') {
        try {
            return JSON.stringify(value);
        } catch (err) {
            log('MQTT: JSON-Konvertierung fehlgeschlagen: ' + err, 'warn');
            return String(value);
        }
    }

    return String(value);
}

function publishState(id, state) {
    if (!id || !state || !isAllowedId(id)) return;

    const payload = valueToPayload(state.val);
    if (payload === null) return;

    const topic = stateIdToTopic(id);

    sendTo(MQTT_INSTANCE, 'sendMessage2Client', {
        topic,
        message: payload,
        retain: RETAIN
    });
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function publishAllStates() {
    let sent = 0;

    for (const root of ROOTS) {
        const ids = [];

        $('state[id=' + root + '.*]').each(id => {
            if (isAllowedId(id)) ids.push(id);
        });

        log('MQTT Bridge: ' + ids.length + ' States unter ' + root + ' gefunden');

        for (const id of ids) {
            try {
                const state = await getStateAsync(id);

                if (state && !state.notExist) {
                    publishState(id, state);
                    sent++;
                }
            } catch (err) {
                log('MQTT Bridge: Fehler beim Lesen von ' + id + ': ' + err, 'warn');
            }

            if (INITIAL_SEND_DELAY_MS > 0) {
                await sleep(INITIAL_SEND_DELAY_MS);
            }
        }
    }

    log('MQTT Bridge: Initialexport abgeschlossen, ' + sent + ' Werte gesendet');
}

// Änderungen aller gewünschten Bereiche überwachen.
// q:'*' sorgt dafür, dass auch States mit Quality != 0 verarbeitet werden.
on({
    id: /^(0_userdata|goodwe_we|hm-rega|hm-rpc)\./,
    change: 'any',
    q: '*'
}, obj => {
    if (!obj || !obj.id || !obj.state) return;
    publishState(obj.id, obj.state);
});

if (PUBLISH_ON_START) {
    setTimeout(() => {
        publishAllStates().catch(err => {
            log('MQTT Bridge: Initialexport fehlgeschlagen: ' + err, 'error');
        });
    }, 3000);
}

log('ioBroker -> MQTT Bridge gestartet: ' + ROOTS.join(', '));
