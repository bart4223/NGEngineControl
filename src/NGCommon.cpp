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
