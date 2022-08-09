//
//  NGSimpleWirelessReceiver.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.08.22.
//

#include "NGSimpleWirelessReceiver.h"

NGSimpleWirelessReceiver::NGSimpleWirelessReceiver() {
    _create();
}

void NGSimpleWirelessReceiver::_create() {
    
}

void NGSimpleWirelessReceiver::registerCallback(int pin,  simpleWirelessReceiverMode mode, simpleWirelessReceiverCallbackFunc callback) {
    registerCallback(pin, mode, callback, SWRNODELAY);
}

void NGSimpleWirelessReceiver::registerCallback(int pin,  simpleWirelessReceiverMode mode, simpleWirelessReceiverCallbackFunc callback, int delay) {
    if (_receiverCallbackCount < MAXSWRCALLBACKOUNT) {
        simpleWirelessReceiverCallback cb;
        cb.pin = pin;
        cb.mode = mode;
        cb.callback = callback;
        cb.delay = delay;
        _receiverCallbacks[_receiverCallbackCount] = cb;
        _receiverCallbackCount++;
    }
}

void NGSimpleWirelessReceiver::initialize() {
    for (int i = 0; i < _receiverCallbackCount; i++) {
        pinMode(_receiverCallbacks[i].pin, INPUT);
    }
}

void NGSimpleWirelessReceiver::processingLoop() {
    bool mature;
    for (int i = 0; i < _receiverCallbackCount; i++) {
        mature = _receiverCallbacks[i].delay == SWRNODELAY;
        if (!mature) {
            mature = (millis() - _receiverCallbacks[i].lastFire) > _receiverCallbacks[i].delay;
        }
        if (mature) {
            switch (_receiverCallbacks[i].mode) {
                case swrmLOW:
                    if (digitalRead(_receiverCallbacks[i].pin) == LOW) {
                        _receiverCallbacks[i].callback();
                        if (_receiverCallbacks[i].delay > SWRNODELAY) {
                            _receiverCallbacks[i].lastFire = millis();
                        }
                    }
                    break;
                case swrmHIGH:
                    if (digitalRead(_receiverCallbacks[i].pin) == HIGH) {
                        _receiverCallbacks[i].callback();
                        if (_receiverCallbacks[i].delay > SWRNODELAY) {
                            _receiverCallbacks[i].lastFire = millis();
                        }
                    }
                    break;
                    
                }
        }
    }
}
