//
//  NGI2CScanner.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.01.22.
//

#include "Wire.h"
#include "NGCommon.h"
#include <NGMemoryObserver.h>
#include "NGI2CScanner.h"

NGI2CScanner::NGI2CScanner() {
    _create();
}

void NGI2CScanner::_create() {
    Wire.begin();
}

void NGI2CScanner::_startScan() {
    Serial.println("I2C Scanner scanning...");
    Serial.print("  ");
    for (byte i = 0; i < 0x10; i++) {
        Serial.print("  ");
        Serial.print(i, HEX);
    }
    Serial.println();
}

void NGI2CScanner::_scan() {
    for (byte i = 0; i < 0x80; i++) {
        if (i % 0x10 == 0)  {
            if (i != 0) {
                Serial.println();
            }
            Serial.print((i + 1) / 0x10);
            Serial.print("  ");
        }
        if (i == 0 || i == 0x7F ) {
            Serial.print("   ");
            continue;
        }
        Wire.beginTransmission(i);
        byte err = Wire.endTransmission();
        if (err == 0x00)  {
            if (i < 0x10) {
                Serial.print("0");
            }
            Serial.print(i, HEX);
            Serial.print(" ");
            _devices++;
        }
        else if (err == 0x04) {
            Serial.print("?? ");
        }
        else {
            Serial.print("__ ");
        }
    }
}

void NGI2CScanner::_finishScan() {
    char log[100];
    sprintf(log, "\n\n%d device(s) found.", _devices);
    Serial.println(log);
}

void NGI2CScanner::scan() {
    _startScan();
    _scan();
    _finishScan();
}

void NGI2CScanner::scanWire() {
    scanWire(DEFTIMEOUT);
}

void NGI2CScanner::scanWire(int timeout) {
    _ensureGlobalSerial(DEFAULTSERIALRATE);
    NGI2CScanner s = NGI2CScanner();
    s.scan();
    observeMemory(timeout);
}
