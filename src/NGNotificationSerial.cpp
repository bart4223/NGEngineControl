//
//  NGNotificationSerial.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#include "NGCommon.h"
#include "NGNotificationSerial.h"

NGNotificationSerial::NGNotificationSerial() {
    _create(DEFAULTSERIALRATE);
}

NGNotificationSerial::NGNotificationSerial(int serialRate) {
    _create(serialRate);
}

void NGNotificationSerial::_create(int serialRate) {
    _serialRate = serialRate;
}

void NGNotificationSerial::initialize() {
    _ensureGlobalSerial(_serialRate);
}

char* NGNotificationSerial::getName() {
    return "Console";
}

void NGNotificationSerial::writeInfo(char* info) {
    Serial.println(info);
}
