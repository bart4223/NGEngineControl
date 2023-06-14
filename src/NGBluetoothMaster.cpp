//
//  NGBluetoothMaster.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 12.06.23.
//

#include "NGCommon.h"
#include "NGBluetooth.h"
#include "NGBluetoothMaster.h"

NGBluetoothMaster::NGBluetoothMaster() {
    NGBluetoothMaster(DEFAULTSERIALRATE);
}

NGBluetoothMaster::NGBluetoothMaster(int SerialRate) {
    _create(SerialRate);
}

void NGBluetoothMaster::_create(int SerialRate) {
    _serialRate = SerialRate;
}

void NGBluetoothMaster::_sendHeader() {
    Serial.write(BT_CMD_HEADER1);
    Serial.write(BT_CMD_HEADER2);
}

void NGBluetoothMaster::_sendKindSoundCheck() {
    Serial.write(BT_CMD_KIND_SOUNDCHECK);
}

void NGBluetoothMaster::_sendKindSwitch() {
    Serial.write(BT_CMD_KIND_SWITCH);
}

void NGBluetoothMaster::initialize() {
    if (!_initialized) {
        _ensureGlobalSerial(_serialRate);
        _initialized = true;
    }
}

void NGBluetoothMaster::sendSoundcheck() {
    _sendHeader();
    _sendKindSoundCheck();
}

void NGBluetoothMaster::sendSwitchCommand(byte context, bool on) {
    _sendHeader();
    _sendKindSwitch();
    Serial.write(context);
    if (on) {
        Serial.write(BT_CMD_KIND_SWITCH_ON);
    } else {
        Serial.write(BT_CMD_KIND_SWITCH_OFF);
    }
}
