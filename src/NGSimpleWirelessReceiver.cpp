//
//  NGSimpleWirelessReceiver.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.08.22.
//

#include "NGSimpleWirelessReceiver.h"

NGSimpleWirelessReceiver::NGSimpleWirelessReceiver() {
    _create(DEFREMOTEID);
}

NGSimpleWirelessReceiver::NGSimpleWirelessReceiver(byte ID) {
    _create(ID);
}

void NGSimpleWirelessReceiver::_create(byte ID) {
    _ID = ID;
}

void NGSimpleWirelessReceiver::_resetCurrentCallback() {
    _currentCallback = SWRNOCURRENTCALLBACK;
}

void NGSimpleWirelessReceiver::registerCallback(int pin, simpleWirelessReceiverCallbackFunc callback) {
    registerCallback(pin, swrmHIGH, callback);
}

void NGSimpleWirelessReceiver::registerCallback(int pin,  simpleWirelessReceiverMode mode, simpleWirelessReceiverCallbackFunc callback) {
    registerCallback(pin, mode, callback, SWRNODELAY);
}

void NGSimpleWirelessReceiver::registerCallback(int pin, simpleWirelessReceiverCallbackFunc callback, int delay) {
    registerCallback(pin, swrmHIGH, callback, delay);
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

void NGSimpleWirelessReceiver::registerCommand(int pin, byte protocol, byte address, byte command) {
    registerCommand(pin, swrmHIGH, protocol, address, command, SWRNODELAY);
}

void NGSimpleWirelessReceiver::registerCommand(int pin, byte protocol, byte address, byte command, int delay) {
    registerCommand(pin, swrmHIGH, protocol, address, command, delay);
}

void NGSimpleWirelessReceiver::registerCommand(int pin, simpleWirelessReceiverMode mode, byte protocol, byte address, byte command, int delay) {
    if (_receiverCallbackCount < MAXSWRCALLBACKOUNT) {
        simpleWirelessReceiverCallback cb;
        cb.pin = pin;
        cb.mode = mode;
        cb.protocol = protocol;
        cb.address = address;
        cb.command = command;
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
    _resetCurrentCallback();
    for (int i = 0; i < _receiverCallbackCount; i++) {
        mature = _receiverCallbacks[i].delay == SWRNODELAY;
        if (!mature) {
            mature = (millis() - _receiverCallbacks[i].lastFire) > _receiverCallbacks[i].delay;
        }
        if (mature) {
            switch (_receiverCallbacks[i].mode) {
                case swrmLOW:
                    if (digitalRead(_receiverCallbacks[i].pin) == LOW) {
                        _currentCallback = i;
                        if (_receiverCallbacks[_currentCallback].protocol == SWRNOPROTOCOL) {
                            _receiverCallbacks[_currentCallback].callback();
                        }
                        if (_receiverCallbacks[_currentCallback].delay > SWRNODELAY) {
                            _receiverCallbacks[_currentCallback].lastFire = millis();
                        }
                        return;
                    }
                    break;
                case swrmHIGH:
                    if (digitalRead(_receiverCallbacks[i].pin) == HIGH) {
                        _currentCallback = i;
                        if (_receiverCallbacks[_currentCallback].protocol == SWRNOPROTOCOL) {
                            _receiverCallbacks[_currentCallback].callback();
                        }
                        if (_receiverCallbacks[_currentCallback].delay > SWRNODELAY) {
                            _receiverCallbacks[_currentCallback].lastFire = millis();
                        }
                        return;
                    }
                    break;
                }
        }
    }
}

bool NGSimpleWirelessReceiver::isCommandReceived() {
    return _currentCallback != SWRNOCURRENTCALLBACK;
}

byte NGSimpleWirelessReceiver::getReceivedCommandProtocol() {
    byte res = 0x00;
    if (_currentCallback != SWRNOCURRENTCALLBACK) {
        res = _receiverCallbacks[_currentCallback].protocol;
    }
    return res;
}

byte NGSimpleWirelessReceiver::getReceivedCommandAddress() {
    byte res = 0x00;
    if (_currentCallback != SWRNOCURRENTCALLBACK) {
        res = _receiverCallbacks[_currentCallback].address;
    }
    return res;
}

byte NGSimpleWirelessReceiver::getReceivedCommand() {
    byte res = 0x00;
    if (_currentCallback != SWRNOCURRENTCALLBACK) {
        res = _receiverCallbacks[_currentCallback].command;
    }
    return res;
}

byte NGSimpleWirelessReceiver::getID() {
    return _ID;
}
