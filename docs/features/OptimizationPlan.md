# Optimierungsplan: NGEngine-Ökosystem

> Stand: 2026-04-13  
> Betrifft: NGEngineCore + NGEngineControl

---

## Übersicht

Die folgenden Optimierungen sind nach Priorität und Aufwand geordnet. Jede Maßnahme ist unabhängig umsetzbar — es gibt keine erzwungene Reihenfolge, außer wo explizit angegeben.

---

## 1. Zirkuläre Abhängigkeit auflösen

**Problem:** `NGEngineCore/examples/` referenziert `NGMemoryObserver`, der in NGEngineControl lebt. Core darf nie von Control abhängen.

**Lösung:** `NGMemoryObserver` in NGEngineCore verschieben — er hat keine Abhängigkeit auf Control-Klassen und ist ein reines AVR-Utility.

**Aufwand:** Klein  
**Priorität:** Hoch — ist ein struktureller Fehler

---

## 2. `library.properties` Versionierung korrigieren

**Problem:** Beide Bibliotheken stehen auf `version=0.1`, obwohl z.B. `NGMotionUnitControl` bei v6.2 ist. Die Versionsnummer ist bedeutungslos.

**Lösung:** Semantische Versionierung einführen (z.B. `1.0.0`). Versions-Bumps bei Breaking Changes. Beide Repos synchron halten, da NGEngineControl von NGEngineCore abhängt.

**Aufwand:** Klein  
**Priorität:** Mittel

---

## 3. Kapazitätsgrenzen pro Klasse dokumentieren

**Problem:** Feste Array-Größen (6 vs. 20 Sequenzen, 3 vs. 10 Object Recognizer) sind über `#ifdef NG_PLATFORM_MEGA`-Guards verstreut. Wer eine neue Klasse einbindet, stolpert erst zur Laufzeit über überschrittene Grenzen.

**Lösung:**

- Konstanten aus den Guards extrahieren und in einem zentralen Header (`NGCapacities.h`) bündeln
- Jede Klasse gibt ihre Limits als `static const` zurück, z.B. `NGMotionUnitControl::MAX_SEQUENCES`
- Optional: zur Compile-Time prüfen mit `static_assert`

**Aufwand:** Mittel  
**Priorität:** Mittel

---

## 4. Einheitliche Fehlerbehandlungsstrategie

**Problem:** `NGExceptionDefinitions.h` definiert ~30 Fehlercodes, aber sie werden inkonsistent verwendet — manche Klassen nutzen sie, andere ignorieren Fehlerzustände stillschweigend. Auf embedded Systemen ist das gefährlich (z.B. I2C-Timeout ohne Rückmeldung).

**Lösung:**

- Eine `NGError`-Konvention einführen: Funktionen, die fehlschlagen können, geben einen Fehlercode zurück (oder setzen ein internes Flag, das per `getLastError()` abgefragt werden kann)
- Mindestens für I2C-Kommunikation (`NGCustomUnitControl`), Sensor-Reads und RTC konsequent anwenden
- Kein C++-Exception-Overhead — reine Integer-Codes

**Aufwand:** Mittel bis Groß  
**Priorität:** Mittel

---

## 5. I2C-Protokoll absichern

**Problem:** Das binäre I2C-Protokoll (Subject + Operation + Name bis 0xFF) hat keine Checksumme, keine ACK-Bestätigung und keinen Timeout-Mechanismus. Ein gestörtes Byte kann zu falschen Motorkommandos führen.

**Lösung:**

- CRC8-Byte am Ende des Rahmens anhängen (kostet 1 Byte, kaum Rechenzeit auf AVR)
- Sender wartet auf ACK-Byte vom Slave, bevor er den nächsten Befehl sendet
- Timeout (z.B. 100 ms) mit Retry-Logik (max. 3 Versuche) im Master

**Aufwand:** Mittel  
**Priorität:** Hoch bei Motoman und anderen Multi-Unit-Projekten

---

## 6. `NGSplash` und Effekt-System vereinheitlichen

**Problem:** `NGSplash` (in Core) verwaltet bis zu 5 `NGIEffect`-Instanzen mit Hardcoded-Limit. `NGOnAirUnitControl` verwaltet bis zu 4 Effekte in eigener Logik. Zwei parallele Mechanismen für dasselbe Problem.

**Lösung:**

- `NGSplash` zu einem allgemeinen `NGEffectSequencer` ausbauen (umbenennen)
- `NGOnAirUnitControl` und künftige Effekt-Controller darauf aufbauen
- Limit als Template-Parameter oder Kapazitäts-Konstante (siehe Punkt 3)

**Aufwand:** Mittel  
**Priorität:** Niedrig bis Mittel

---

## 7. Bluetooth-Protokoll und Wireless-Protokoll angleichen

**Problem:** `NGBluetoothMaster/Slave` nutzt einen eigenen 4-Byte-Rahmen (`0x2A`/`0x17` Header, Kind-Byte, Wert-Byte). `NGSimpleWirelessReceiver` hat ein anderes Format. Beide lösen dasselbe Problem (Fernsteuerung), aber mit inkompatibler Framing-Logik.

**Lösung:**

- Gemeinsamen `NGRemoteProtocol`-Header definieren (Präambel, Länge, Kind, Payload, CRC)
- Bluetooth- und Wireless-Implementierungen darauf aufsetzen
- Erleichtert künftig den Austausch des Übertragungsmediums ohne Protokolländerung

**Aufwand:** Groß  
**Priorität:** Niedrig (nur relevant, wenn beide Protokolle gleichzeitig in einem Projekt genutzt werden)

---

## 8. Beispiele und Projekte mit Mindest-Doku versehen

**Problem:** 50+ Beispiele und 13 Projekte sind ohne jede Beschreibung — weder im Sketch-Kopf noch in einer README. Was macht `buggy.ino` konkret? Welche Hardware braucht man?

**Lösung:**

- Jedes Projekt bekommt eine `README.md` mit: Zweck, benötigte Hardware (inkl. Pinbelegung), benötigte Bibliotheken
- Beispiel-Sketche bekommen einen kurzen Kommentarblock am Anfang

**Aufwand:** Klein pro Datei, viel insgesamt  
**Priorität:** Niedrig (Komfort, kein funktionaler Gewinn)

---

## Zusammenfassung

| # | Maßnahme | Aufwand | Priorität |
| --- | --- | --- | --- |
| 1 | Zirkuläre Abhängigkeit auflösen | Klein | Hoch |
| 2 | Versionierung korrigieren | Klein | Mittel |
| 3 | Kapazitätsgrenzen zentralisieren | Mittel | Mittel |
| 4 | Einheitliche Fehlerbehandlung | Mittel–Groß | Mittel |
| 5 | I2C-Protokoll absichern (CRC + ACK) | Mittel | Hoch |
| 6 | Effekt-System vereinheitlichen | Mittel | Niedrig–Mittel |
| 7 | Remote-Protokoll vereinheitlichen | Groß | Niedrig |
| 8 | Projekt-Dokumentation | Klein/Stück | Niedrig |
