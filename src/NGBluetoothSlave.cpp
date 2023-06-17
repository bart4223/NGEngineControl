//
//  NGBluetoothSlave.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.06.23.
//

#include "NGCommon.h"
#include "NGBluetoothSlave.h"

NGBluetoothSlave::NGBluetoothSlave() {
    NGBluetoothSlave(DEFAULTSERIALRATE);
}

NGBluetoothSlave::NGBluetoothSlave(int SerialRate) {
    _create(SerialRate);
}

void NGBluetoothSlave::_create(int SerialRate) {
    _serialRate = SerialRate;
}

void NGBluetoothSlave::_clearCurrent() {
    _currentIndex = 0;
    _currentKind = BT_NO_KIND;
    _currentContext = BT_NO_CONTEXT;
}

void NGBluetoothSlave::initialize() {
    if (!_initialized) {
        _ensureGlobalSerial(_serialRate);
        _initialized = true;
    }
}

void NGBluetoothSlave::setLogging(bool logging) {
    _logging = logging;
}

bool NGBluetoothSlave::getLogging() {
    return _logging;
}

void NGBluetoothSlave::registerSwitchCallback(bluetoothSlaveSwitchCallbackFunc callback) {
    _callbackSwitch = callback;
}

void NGBluetoothSlave::registerCounterCallback(bluetoothSlaveCounterCallbackFunc callback) {
    _callbackCounter = callback;
}

void NGBluetoothSlave::processingLoop() {
    while (Serial.available() > 0) {
        byte b = Serial.read();
        switch (_currentIndex) {
            case 0:
                if (b == BT_CMD_HEADER1) {
                    _currentIndex++;
                }
                break;
            case 1:
                if (b == BT_CMD_HEADER2) {
                    _currentIndex++;
                    if (_logging) {
                        Serial.println("BT Header received");
                    }
                }
                break;
            case 2:
                switch (b) {
                    case BT_CMD_KIND_SOUNDCHECK:
                        if (_logging) {
                            Serial.println("BT Soundcheck received");
                        }
                        _clearCurrent();
                        break;
                    case BT_CMD_KIND_SWITCH:
                        if (_logging) {
                            Serial.println("BT Switch received");
                        }
                        _currentKind = b;
                        _currentIndex++;
                        break;
                    case BT_CMD_KIND_COUNTER:
                        if (_logging) {
                            Serial.println("BT Counter received");
                        }
                        _currentKind = b;
                        _currentIndex++;
                        break;
                    default:
                        _clearCurrent();
                }
                break;
            case 3:
                _currentContext = b;
                _currentIndex++;
                break;
            case 4:
                switch (_currentKind) {
                    case BT_CMD_KIND_SWITCH:
                        if (_callbackSwitch != nullptr) {
                            _callbackSwitch(_currentContext, b == BT_CMD_KIND_SWITCH_ON);
                        }
                        _clearCurrent();
                        break;
                    case BT_CMD_KIND_COUNTER:
                        if (_callbackCounter != nullptr) {
                            _callbackCounter(_currentContext, b);
                        }
                        _clearCurrent();
                        break;}
            default:
                _clearCurrent();
        }
    }
}
