#pragma once
#include <Arduino.h>
const char WEB_APP[] PROGMEM = R"VWEB(
<!doctype html><html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Victron Display</title><style>
body{font-family:Arial,sans-serif;background:#0b1220;color:#eef3f8;margin:0}.w{max-width:980px;margin:auto;padding:16px}
.c{background:#121d2e;border:1px solid #2c405d;border-radius:10px;padding:12px;margin:10px 0}.g{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:10px}
input,select,button{box-sizing:border-box;width:100%;padding:8px;margin:3px 0 7px;background:#0b1422;color:#fff;border:1px solid #40516b;border-radius:6px}
button{background:#1268a8;font-weight:bold}.muted{color:#a8b6c7}.live{font-size:20px}
</style></head><body><div class="w"><h1>Victron Display <span id="ver">V4.2.0</span></h1>
<div class="c"><b>Webinterface aktiv</b><div id="sys" class="muted">Lade Systemstatus...</div><div class="muted">Entwickler: Ebner Stephan</div></div>
<div class="c"><h2>Live</h2><div id="pv" class="g"></div></div>
<form id="cfgform"><h2>Kacheln</h2><div id="tiles" class="g"></div>
<div class="c"><h2>Display / OTA</h2>
<label>Displayname / HOME-Titel</label><input id="displayname" name="displayname" maxlength="24" placeholder="Victron Home">
<label>Display aus nach Minuten (0 = nie)</label><input id="timeout" name="timeout" type="number" min="0" max="240">
<label>Arduino OTA Hostname</label><input id="otahost" name="otahost">
<label>Eigenes Arduino OTA Passwort</label><input id="otapass" name="otapass" type="password" placeholder="leer = unveraendert">
<label><input style="width:auto" type="checkbox" name="clearota" value="1"> OTA Passwort entfernen</label>
<button type="submit">Konfiguration speichern</button><div id="msg"></div></div></form>
<div class="g"><div class="c"><h2>MQTT Topics</h2><div id="topics" class="muted">Lade...</div></div>
<div class="c"><h2>Software Update</h2><div id="upd" class="muted">Noch nicht geprüft</div><button onclick="checkUpdate()" type="button">Nach Update suchen</button><button id="installbtn" onclick="installUpdate()" type="button" style="display:none;background:#198754">Update installieren</button><button onclick="location.href='/update'">Firmware manuell hochladen</button>
<button onclick="location.href='/export'">Konfiguration exportieren</button>
<button onclick="location.href='/health'">Webserver Test</button></div></div></div>
<script>
function byId(x){return document.getElementById(x);}
function esc(x){x=String(x==null?'':x);return x.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;');}
function getJson(url,ok,fail){var x=new XMLHttpRequest();x.open('GET',url,true);x.onreadystatechange=function(){if(x.readyState===4){if(x.status===200){try{ok(JSON.parse(x.responseText));}catch(e){if(fail)fail(e);}}else if(fail)fail(x.status);}};x.send();}
function loadCfg(){
 getJson('/api/config',function(c){
  byId('ver').innerHTML='V'+esc(c.version);byId('displayname').value=c.displayname||'Victron Home';byId('timeout').value=c.timeout;byId('otahost').value=c.otahost||'victron-display';
  var h='',i,t,d;
  for(i=0;i<c.tiles.length;i++){t=c.tiles[i];
   h+='<div class="c"><h3>Kachel '+(i+1)+'</h3><label>Name</label><input name="l'+i+'" value="'+esc(t.label)+'"><label>MQTT Topic</label><input name="t'+i+'" value="'+esc(t.topic)+'"><label>Einheit</label><input name="u'+i+'" value="'+esc(t.unit)+'"><label>Nachkommastellen</label><select name="d'+i+'">';
   for(d=0;d<4;d++)h+='<option value="'+d+'"'+(d==t.decimals?' selected':'')+'>'+d+'</option>';
   h+='</select><label>Darstellung</label><select name="s'+i+'"><option value="0"'+(t.style==0?' selected':'')+'>Zahl</option><option value="1"'+(t.style==1?' selected':'')+'>Balken</option><option value="2"'+(t.style==2?' selected':'')+'>Sparkline</option></select><label>Skala min</label><input name="lo'+i+'" value="'+(t.min==null?'':t.min)+'"><label>Skala max</label><input name="hi'+i+'" value="'+(t.max==null?'':t.max)+'"></div>';
  } byId('tiles').innerHTML=h;
 },function(){byId('msg').innerHTML='Konfiguration konnte nicht geladen werden.';});
}
function loadLive(){getJson('/api/status',function(j){byId('sys').innerHTML='IP '+esc(j.ip)+' | RSSI '+j.rssi+' dBm | MQTT '+(j.mqtt?'verbunden':'getrennt')+' | Heap '+j.heap;var h='',i;for(i=0;i<j.tiles.length;i++)h+='<div class="c"><b>'+esc(j.tiles[i].label)+'</b><div class="live">'+esc(j.tiles[i].value)+' '+esc(j.tiles[i].unit)+'</div></div>';byId('pv').innerHTML=h;h='';for(i=0;i<j.topics.length;i++)h+='<div>'+esc(j.topics[i].n)+' = '+j.topics[i].v+'</div>';byId('topics').innerHTML=h||'Noch keine Topics';},function(){byId('sys').innerHTML='API nicht erreichbar - /health testen';});}
function checkUpdate(){byId('upd').innerHTML='Pruefe GitHub...';getJson('/api/update-check',function(j){byId('upd').innerHTML=esc(j.message)+' | Installiert V'+esc(j.current)+(j.latest?' | GitHub V'+esc(j.latest):'');byId('installbtn').style.display=j.available?'block':'none';},function(){byId('upd').innerHTML='Update-Pruefung fehlgeschlagen';});}
function installUpdate(){if(!confirm('Neue Firmware von GitHub installieren?'))return;byId('upd').innerHTML='Update wird gestartet...';var x=new XMLHttpRequest();x.open('POST','/api/github-update',true);x.onreadystatechange=function(){if(x.readyState===4)byId('upd').innerHTML=x.responseText||('HTTP '+x.status);};x.send('');}
byId('cfgform').onsubmit=function(e){e.preventDefault();byId('msg').innerHTML='Speichere...';var form=byId('cfgform'),els=form.elements,parts=[],i,el;for(i=0;i<els.length;i++){el=els[i];if(!el.name||el.disabled)continue;if((el.type==='checkbox'||el.type==='radio')&&!el.checked)continue;parts.push(encodeURIComponent(el.name)+'='+encodeURIComponent(el.value));}var body=parts.join('&');var x=new XMLHttpRequest();x.open('POST','/api/save',true);x.setRequestHeader('Content-Type','application/x-www-form-urlencoded; charset=UTF-8');x.onreadystatechange=function(){if(x.readyState===4){byId('msg').innerHTML=x.status===200?x.responseText:'Fehler '+x.status;if(x.status===200){setTimeout(function(){loadCfg();loadLive();},300);}}};x.send(body);};
loadCfg();loadLive();setInterval(loadLive,2000);setTimeout(checkUpdate,1200);
</script></body></html>
)VWEB";