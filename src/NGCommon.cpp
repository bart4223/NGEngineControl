//
//  NGCommon.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include <NGCommon.h>

void _ensureGlobalSerial(int serialRate) {
    if (!_globalSerialStarted) {
        Serial.begin(serialRate);
        _globalSerialStarted = true;
    }
}

bool getYesOrNo() {
    return (random(0, 2) == 0);
}

bool IsButtonPressed(int pin) {
    return IsSwitchOn(pin);
}

bool IsSwitchOn(int pin) {
    pinMode(pin, INPUT_PULLUP);
    return digitalRead(pin) == LOW;
}
