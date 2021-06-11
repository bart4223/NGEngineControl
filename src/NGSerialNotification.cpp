//
//  NGSerialNotification.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#include "NGCommon.h"
#include "NGSerialNotification.h"

NGSerialNotification::NGSerialNotification() {
    _create(DEFAULTSERIALRATE);
}

NGSerialNotification::NGSerialNotification(int serialRate) {
    _create(serialRate);
}

void NGSerialNotification::_create(int serialRate) {
    _serialRate = serialRate;
}

void NGSerialNotification::initialize() {
    _ensureGlobalSerial(_serialRate);
}

char* NGSerialNotification::getName() {
    return "Serial";
}

void NGSerialNotification::writeInfo(char* info) {
    Serial.println(info);
}
