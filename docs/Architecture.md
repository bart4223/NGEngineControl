# Architecture: NGEngineControl

> Stand: 2026-04-13  
> Basis-Bibliothek: [NGEngineCore]

---

## Überblick

**NGEngineControl** ist eine Arduino-C++-Bibliothek für Robotik, Automatisierung und eingebettete Hardwaresteuerung. Sie baut direkt auf **NGEngineCore** auf, das die Abstraktionsschichten (Interfaces, Grafikprimitiven, Schriften, Utilities) liefert.

```text
[Sketch / Projekt-Sketch (.ino)]
        │
        ▼
[NGEngineControl]  ◄── Konkrete Treiber, Unit-Controller, Verhalten
        │
        ▼
[NGEngineCore]     ◄── Interfaces, Datentypen, Fonts, Utilities
        │
        ▼
[Arduino SDK / Drittbibliotheken]
```

### Library-Metadaten

| Eigenschaft | NGEngineControl | NGEngineCore |
| --- | --- | --- |
| Version | 0.1 | 0.1 |
| Autor | Bart4223 | Bart4223 |
| Architektur | `*` (alle Arduino-Plattformen) | `*` (alle Arduino-Plattformen) |
| GitHub | bart4223/NGEngineControl | bart4223/NGEngineCore |

---

## Verzeichnisstruktur

```text
NGEngineControl/
├── src/
│   ├── Apps/              Unit-Controller für spezifische Anwendungen
│   ├── Effects/           Visuelle Effektklassen (NGIEffect-Implementierungen)
│   ├── Sensors/           Sensorklassen
│   ├── Specs/             Uhr-/Watch-Subsystem (Zifferblätter, Komplikationen)
│   ├── Visuals/           LED-Strip- und Display-Treiber
│   └── (root)             ~90 .h/.cpp-Dateien — Kernbibliotheksklassen
├── examples/              50+ .ino-Sketche für einzelne Komponenten
├── projects/              13 vollständige Projekt-Sketche
│   ├── anchorman/
│   ├── binaryclock/
│   ├── bluetoothremotecontrol/
│   ├── buggy/
│   ├── candlearch/
│   ├── currentmeasurement/
│   ├── doorguard/
│   ├── irrigationsystem/
│   ├── littlebigclock/
│   ├── motoman/           (3 Units: centralunit, motionunit, toolunit)
│   ├── onair/
│   ├── speedy/
│   ├── ultimatemachine/
│   └── wirelessremotecontrol/
└── docs/
    ├── Architecture.md    (diese Datei)
    ├── Pages.txt
    ├── ToDo.md
    └── images/
```

---

## Architekturprinzipien

### 1. Geschichtete Architektur

NGEngineCore definiert Abstraktionen (Interfaces, Datentypen). NGEngineControl liefert konkrete Implementierungen. Projekte kombinieren beides in Arduino-Sketchen.

### 2. Interface-gesteuerte Grafik

Alle Ausgabeflächen implementieren `NGIPaintableComponent` aus NGEngineCore. Code, der auf einer Dot-Matrix zeichnet, funktioniert identisch gegen einen LED-Strip oder ein TFT-Display.

| NGEngineCore Interface | NGEngineControl Implementierungen |
| --- | --- |
| `NGIPaintableComponent` | `NGColorDotMatrix`, `NGColorLEDStrip`, `NGCircleLEDStrip`, `NGTFTDisplay`, `NG8x8DotMatrix` |
| `NGIExtendedPaintableComponent` | `NGCircleLEDStrip`, `NGTFTDisplay` |
| `NGINotification` | `NGSerialNotification`, `NGLCDNotification`, `NGOLEDNotification`, `NGMorseToneNotification` |
| `NGIEffect` | `NGColorDotMatrixEffectText`, `NGSimpleLEDEffect`, `NGSimpleColorLEDStripEffect`, `NGSimpleCircleLEDStripEffect`, `NGSymbolCircleLEDStripEffect`, `NGSoundMachineEffect` |
| `NGITestableComponent` | `NGFlashingLight`, `NGLightSensor`, `NGColorLEDStrip`, `NGCircleLEDStrip`, `NGTFTDisplay`, `NG8x8DotMatrix` |

### 3. I2C Multi-Unit-Kommunikation

Ein `NGCentralUnitControl` (Master) sendet binäre Befehle über den I2C-Bus an Slave-Units. Das Protokoll ist ein 15-Byte-Rahmen:

```text
Byte 0: Subject   — 0x00 None | 0x01 Engine | 0x02 Joint | 0x03 Gripper
Byte 1: Operation — z.B. 0x01 RunForward | 0x02 RunBackward | 0x03 Stop …
Byte 2+: Name     — bis zu 9 Bytes, terminiert mit 0xFF
```

### 4. Strategie-Muster für Fahrverhalten

`NGCustomMotionControl` hält eine austauschbare `NGCustomMotionMimic`-Instanz (Strategy Pattern):

| Implementierung | Verhalten |
| --- | --- |
| `NGCaveExplorer` | Autonome Hindernisumfahrung (Ultraschall/ToF) |
| `NGBotRetriever` | Autonomes Rückholverhalten |
| `NGSimpleMotionMimic` | Einfaches vordefiniertes Verhalten |
| `NGVoidMotionMimic` | No-Op Platzhalter |

### 5. Event-Loop-Modell

Alle Units folgen dem Arduino-Muster `setup()` + `loop()`. Jede Komponente implementiert `initialize()` und `processingLoop()`.

### 6. Plattform-Branching

`NG_PLATFORM_MEGA`-Präprozessor-Guards erhöhen Kapazitätsgrenzen:

| Ressource | AVR/Uno | Mega |
| --- | --- | --- |
| Motion Sequences | 6 | 20 |
| IR-Funktionen | 3 | 10 |
| Object Recognizer | 3 | 10 |

---

## Klassen-Inventar

### Abstrakte Basisklassen

| Klasse | Datei | Zweck |
| --- | --- | --- |
| `NGCustomUnitControl` | `src/NGCustomUnitControl.h/.cpp` | Basis aller Unit-Controller: I2C, IR-Remote, Sound, Keypad, RTC, Notifications, Splash |
| `NGCustomSteeringControl` | `src/NGCustomSteeringControl.h/.cpp` | Abstrakte Lenkung: `run`, `stop`, `turnForward/Backward`, `runFullSpeed*` |
| `NGCustomMotionControl` | `src/NGCustomMotionControl.h/.cpp` | Abstrakte Bewegungssteuerung: Lenkung, Sequenzen, Object Recognizer, IR-Remote |
| `NGCustomMotionMimic` | `src/NGCustomMotionMimic.h/.cpp` | Abstrakte Verhaltens-KI: `determineNextMotionSequenceKind`, `thinkingDelay` |
| `NGCustomObjectRecognizer` | `src/NGCustomObjectRecognizer.h/.cpp` | Abstrakte Sensor-Hülle: `detected()`, `hasDetected()`, `getCloseness()` |
| `NGCustomJingle` | `src/NGCustomJingle.h/.cpp` | Abstrakter Jingle-Player: Frequenz-/Beat-Arrays, Tempo, Cursor |
| `NGCustomWatchDial` | `src/Specs/NGCustomWatchDial.h/.cpp` | Abstrakte Uhr: setzt Stunde/Minute/Sekunde, bis zu 3 Komplikationen |
| `NGCustomWatchComplication` | `src/Specs/NGCustomWatchComplication.h/.cpp` | Abstrakte Komplikation (Sub-Zifferblatt): `processingLoop()` |

### Unit-Controller

| Klasse | Version | Zweck |
| --- | --- | --- |
| `NGUnitControl` | 1.2 | Roboterarm/Servo-Unit: Engines, Joints, Gripper; empfängt I2C-Befehle |
| `NGMotionUnitControl` | 6.2 | Mobile Roboter-Bewegungsunit: Sequenzen, Lenkung, Blinklichter, Laser, IR |
| `NGCentralUnitControl` | 2.0 | Master-Controller: bis zu 3 Sub-Units, 6 Komponenten; sendet I2C-Befehle |
| `NGDoorGuardUnitControl` | 1.2 | Türwächter: überwacht bis zu 3 magnetische Hall-Sensor-Türen |
| `NGLittleBigClockUnitControl` | 1.8 | Uhr-Anwendung: steuert `NGCustomWatchDial` mit periodischer Aktualisierung |
| `NGOnAirUnitControl` | 1.5 | „On Air"-Schild: bis zu 4 visuelle Effekte, optionaler 1-Wire-Temperatursensor |
| `NGAnchormanUnitControl` | — | Anchorman-Roboter |
| `NGBinaryClockUnitControl` | — | Binär-Uhr |
| `NGBluetoothRemoteUnitControl` | — | Bluetooth-Fernsteuerung |
| `NGCandleArchUnitControl` | — | Lichtbogen-Steuerung |
| `NGCurrentMeasurementUnitControl` | — | Strommessungs-Anzeige |
| `NGIrrigationUnitControl` | — | Bewässerungssystem |
| `NGUltimateMachineUnitControl` | — | Ultimate Machine (Kippschalter-Spielzeug) |
| `NGWirelessRemoteUnitControl` | — | 433-MHz-Funkfernsteuerung |
| `NGRemoteMotionControl` | — | Ferngesteuerte Bewegungserweiterung |

### Hardware-Treiber (Motoren & Aktoren)

| Klasse | Zweck |
| --- | --- |
| `NGEngineControl` | DC-Motor-Treiber: ENGINE_0–3 auf PWM-Pins; Geschwindigkeit, Richtung |
| `NGJointControl` | Robotergelenk: Motor + Analogtransducer; `move(targetRad)` |
| `NGGripperControl` | Greifer: motorbasiertes Greifen/Lösen mit konfigurierbaren Delays |
| `NGServoControl` | Servo-Motor (Arduino Servo.h) |
| `NGRelaisControl` | Relais-Schalter |
| `NGPumpControl` | Wasserpumpe |
| `NGLaserCannon` | Laser-Modul (Ein/Aus) |
| `NGJoystickControl` | Analoger Joystick |
| `NGDigitalPotentiometer` | SPI-Digitalpotentiometer |

### Lenkung

| Klasse | Zweck |
| --- | --- |
| `NGSteeringControl` | Differenzialantrieb: linker/rechter Motor mit Offset-Kompensation |
| `NGCarSteeringControl` | Ackermann-Lenkung: Antriebsmotor + Servo-Lenkung |
| `NGCaterpillarSteeringControl` | Raupen-/Panzer-Lenkung: Heck- + Bug-Motorpaar |

### Bewegungssequenzen

| Element | Zweck |
| --- | --- |
| `NGMotionSequenceStorage` | Speichert Bewegungssequenzen (6 auf Uno, 20 auf Mega); je bis zu 5 Items |
| `motionSequenceKind` | `mskNone`, `mskStraight`, `mskLeft`, `mskRight`, `mskStop`, `mskBack`, `mskFullTurn` |
| `motionSequenceItem` | `{turn, direction, speed, light, duration}` |
| `flashingLightSide` | `flsNone`, `flsBoth`, `flsLeft`, `flsRight`, `flsBrake` |

### Visuelle Ausgabe

| Klasse | Ext. Abhängigkeit | Zweck |
| --- | --- | --- |
| `NGColorDotMatrix` | rgbMatrix | 8×8 RGB-LED-Matrix; implementiert `NGIPaintableComponent` |
| `NGColorLEDStrip` | NeoPixelBus | WS2812x adressierbarer LED-Strip; mehrere Layouts; Helligkeit |
| `NGCircleLEDStrip` | NeoPixelBus | Erweiterter LED-Strip mit konzentrischer Ringunterstützung |
| `NGTFTDisplay` | TFT, SPI | Arduino-TFT-Display; vollständige Zeichen-API |
| `NG8x8DotMatrix` | LedControl | MAX7219-basierte 8×8-Monochrom-Dot-Matrix |
| `NGSimpleLED` | — | Einzelne digitale LED |
| `NGDuoLED` | — | Zweifarben-LED |
| `NGColorLED` | — | RGB-LED (einzelne Pins) |
| `NGFlashingLight` | — | Zeitgesteuerte blinkende LED; implementiert `NGITestableComponent` |
| `NG7SegmentDisplay` | — | Einstellige 7-Segment-Anzeige |
| `NGMulti7SegmentDisplay` | — | Mehrstellige 7-Segment-Anzeige |

### Dot-Matrix-Zeichenhilfen

| Klasse | Zweck |
| --- | --- |
| `NGColorDotMatrixBinaryDigit` | Binäre (0/1) Ziffer auf Dot-Matrix |
| `NGColorDotMatrixCharDigit` | Zeichen mit Font auf Dot-Matrix |
| `NGColorDotMatrixDecimalDigit` | Dezimalziffer (0–9) auf Dot-Matrix |
| `NGColorDotMatrixCustomDigit` | Benutzerdefiniertes Bitmap-Zeichen |
| `NGColorDotMatrixFuse` | Fortschrittsbalken / Color-Fuse |
| `NGColorDotMatrixGradientPoint` | Verlaufsfarbiger Punkt |
| `NGColorDotMatrixText` | Textrendering |

### Visuelle Effekte (implementieren `NGIEffect`)

| Klasse | Zweck |
| --- | --- |
| `NGColorDotMatrixEffectText` | Lauftext-/Statischer-Text-Effekt auf Dot-Matrix |
| `NGSimpleLEDEffect` | Einfacher LED-Blink/Fade-Effekt |
| `NGSimpleColorLEDStripEffect` | Farb-Cycling/Chasing auf LED-Strip |
| `NGSimpleCircleLEDStripEffect` | Kreis-Sweep-Effekt auf Circle-LED-Strip |
| `NGSymbolCircleLEDStripEffect` | Symbol/Icon-Darstellung auf Circle-LED-Strip |
| `NGSoundMachineEffect` | Sound-Wiedergabe als `NGIEffect` |

### Benachrichtigungen (implementieren `NGINotification`)

| Klasse | Ext. Abhängigkeit | Zweck |
| --- | --- | --- |
| `NGSerialNotification` | — | Ausgabe auf Arduino-Serial |
| `NGLCDNotification` | LiquidCrystal_I2C | I2C-LCD-Display (z.B. 16×2, 20×4) |
| `NGOLEDNotification` | SSD1306Ascii | SSD1306-OLED (128×64 und 128×32) |
| `NGMorseToneNotification` | — | Morse-Code-Ausgabe via Ton |

### Sensoren

| Klasse | Ext. Abhängigkeit | Sensor-Typ |
| --- | --- | --- |
| `NGUltrasonicObjectRecognizer` | — | HC-SR04 Ultraschall (Trigger/Echo-Pins) |
| `NGTimeOfFlightObjectRecognizer` | VL53L0X | VL53L0X ToF Laser-Distanzsensor |
| `NGContactObjectRecognizer` | — | Digitaler Kontakt-/Bumper-Sensor |
| `NGLightSensor` | — | Analoger LDR-Sensor; bis 5 Schwellwerte |
| `NGHallSensor` | — | Magnetischer Hall-Effekt-Sensor |
| `NGGyroscope` | Wire (I2C) | MPU-6050 Gyroskop/Beschleunigungsmesser |
| `NGCompass` | — | Kompass/Magnetometer |
| `NGSoilMoistureSensor` | — | Kapazitiver Bodenfeuchtigkeitssensor |
| `NGCurrentSensor` | — | Strommessungssensor |
| `NGTemperatureSensor` | DHT | DHT11/DHT22 Temperatur + Luftfeuchtigkeit |
| `NGOneWireTemperatureSensor` | DallasTemperature | DS18B20 1-Wire-Temperatursensor |
| `NGSimpleDigitalSensor` | — | Generischer Digitaleingang |

### Kommunikation

| Klasse | Zweck |
| --- | --- |
| `NGBluetoothMaster` | HC-05 Bluetooth Master: sendet soundcheck/switch/counter-Befehle (4-Byte-Rahmen) |
| `NGBluetoothSlave` | HC-05 Bluetooth Slave: empfängt und parst gerahmte Befehle |
| `NGSimpleWirelessReceiver` | 433-MHz-Funkempfänger |
| `NG4x4Keypad` | 4×4-Matrix-Tastenfeld |
| `NGI2CScanner` | I2C-Bus-Scanner-Utility |
| `NGQuestionDialog` | Interaktiver Ja/Nein-Dialog über Serial |

### Uhr-/Watch-Subsystem (`src/Specs/`)

```text
NGLittleBigClockUnitControl
    └── NGCustomWatchDial (konkret: NGDotMatrixWatchDial)
            ├── NGCustomWatchComplication [0..2]
            │       └── NGDotMatrixWatchCompilationSecondIndicator
            └── NGIPaintableComponent (z.B. NGColorDotMatrix)
                    └── NGColorDotMatrixDecimalDigit × 6 (HH:MM:SS)
```

### Sound-System

```text
NGSoundMachine
    └── NGCustomJingle [0..9]
            ├── NGJingleAlarm
            ├── NGJingleBackward
            ├── NGJingleBeep
            ├── NGJingleBoot
            ├── NGJingleChristmasSong
            ├── NGJingleGorilla
            ├── NGJingleHelloDude
            ├── NGJingleJingleBells
            ├── NGJingleMorse{Dit,Dah,BreakLetter,BreakWord}
            ├── NGJinglePopcorn
            ├── NGJingleSuperMario / NGJingleSuperMarioShort
            └── NGJingleThinking

NGMorseToneGenerator  — Text-zu-Morse via NGSoundMachine
```

### Utilities

| Klasse | Zweck |
| --- | --- |
| `NGMemoryObserver` | `freeMemory()` + `observeMemory()` — AVR-Heap-Monitoring |
| `NGRealTimeClock` | DS3231-RTC via RTClib; Zeitabfrage, Einstellung, `isXMas()` |

---

## Externe Abhängigkeiten

| Bibliothek | Verwendet von |
| --- | --- |
| **NGEngineCore** | Gesamte Bibliothek (alle Interfaces, Typen, Fonts) |
| `LiquidCrystal_I2C` | `NGLCDNotification` |
| `SSD1306Ascii` | `NGOLEDNotification` |
| `NeoPixelBus` | `NGColorLEDStrip`, `NGCircleLEDStrip` |
| `TFT`, `SPI` | `NGTFTDisplay` |
| `LedControl` | `NG8x8DotMatrix` |
| `RTClib` | `NGRealTimeClock` |
| `DHT` | `NGTemperatureSensor` |
| `DallasTemperature` | `NGOneWireTemperatureSensor` |
| `VL53L0X` | `NGTimeOfFlightObjectRecognizer` |
| `rgbMatrix` | `NGColorDotMatrix` |
| `IRremote` | Projekt-Sketche (z.B. `centralunit.ino`) |
| `Wire` (I2C, Arduino) | `NGCustomUnitControl` (Inter-Unit-Kommunikation) |

---

## Reale Projekte

| Projekt | Units | Schlüsselkomponenten |
| --- | --- | --- |
| **Motoman** (Roboterarm) | 3 | `NGCentralUnitControl`, `NGUnitControl`, `NGMotionUnitControl`, I2C, IR-Remote, LCD |
| **Buggy** (Roboter-Auto) | 1 | `NGMotionUnitControl`, `NGSteeringControl`, `NGCaveExplorer` |
| **Speedy** (Auto) | 1–2 | `NGCarSteeringControl`, Bewegungssequenzen |
| **CandleArch** | 1 | `NGCandleArchUnitControl`, Farb-LED-Effekte |
| **LittleBigClock** | 1 | `NGLittleBigClockUnitControl`, `NGDotMatrixWatchDial`, RTC |
| **OnAir** | 1 | `NGOnAirUnitControl`, `NGCircleLEDStrip`, Effekte, Temperatur |
| **DoorGuard** | 1 | `NGDoorGuardUnitControl`, `NGHallSensor`, `NGIEffect` |
| **IrrigationSystem** | 1 | `NGIrrigationUnitControl`, `NGSoilMoistureSensor`, `NGPumpControl` |
| **BinaryClock** | 1 | `NGBinaryClockUnitControl`, `NGColorDotMatrix`, RTC |
| **WirelessRemote** | 2 | `NGWirelessRemoteUnitControl`, `NGSimpleWirelessReceiver` |
| **BluetoothRemote** | 2 | `NGBluetoothMaster`, `NGBluetoothRemoteUnitControl` |
| **Anchorman** | 1 | `NGAnchormanUnitControl` |
| **UltimateMachine** | 1 | `NGUltimateMachineUnitControl` |
