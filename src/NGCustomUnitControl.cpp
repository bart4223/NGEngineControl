//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGCustomUnitControl.h"

void setGlobalUnit(NGCustomUnitControl *unit) {
    _globalUnit = unit;
}

bool hasGlobalUnit() {
    return _globalUnit != nullptr;
}

void globalUnitReceiveDataStart() {
    if (hasGlobalUnit) {
        _globalUnit->receiveDataStart();
    }
}

void globalUnitReceivedData(int index, byte data) {
    if (hasGlobalUnit) {
        _globalUnit->receivedData(index, data);
    }
}

void globalUnitReceiveDataFinish(int count) {
    if (hasGlobalUnit) {
        _globalUnit->receiveDataFinish(count);
    }
}

void globalUnitRequestData(byte* data) {
    if (hasGlobalUnit) {
        return _globalUnit->requestData(data);
    }
}

void NGCustomUnitControl::_create(char* name, byte address, int serialRate) {
    _name = name;
    _address = address;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
    if (_createSoundMachine) {
        _soundMachine = new NGSoundMachine();
    }
}

void NGCustomUnitControl::_clearState() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(1);
    }
}

void NGCustomUnitControl::_writeState() {
    char state[100];
    _clearState();
    #ifdef NG_PLATFORM_MEGA
    if (_rtc != nullptr) {
        sprintf(state, "%s %s wM%d (C) by NG 2021-%s", _name, _version, _workMode, _rtc->getShortYearAsText());
    } else {
        sprintf(state, "%s %s wM%d (C) by NG MMXXI-VI", _name, _version, _workMode);
    }
    #else
    sprintf(state, "%s %s wM%d", _name, _version, _workMode);
    #endif
    if (_rtc != nullptr) {
        sprintf(state, "%s %s", state, _rtc->getDateAsText());
    }
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(state, 1, 0);
    }
}

void NGCustomUnitControl::_writeTime() {
    if (_rtc != nullptr) {
        writeInfo(_rtc->getTimeAsText());
    }
}

void NGCustomUnitControl::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
}

int NGCustomUnitControl::_registerJingle(NGCustomJingle *jingle) {
    if (_soundMachine != nullptr) {
        if (_soundMachine->getJingleCount() < _soundMachine->getMaxJingleCount()) {
            return _soundMachine->registerJingle(jingle);
        } else {
            _raiseException(ExceptionTooMuchJingleCount);
        }
    } else {
        _raiseException(ExceptionNoSoundMachine);
    }
    return NOJINGLE;
}

void NGCustomUnitControl::_playJingleBoot() {
    if (_jingleBoot != NOJINGLE) {
        _playJingle(_jingleBoot);
    }
}

void NGCustomUnitControl::_playJingleStartup() {
    if (_jingleStartup != NOJINGLE) {
        for (int i = 0; i < _jingleStartupLoops; i++) {
            _playJingle(_jingleStartup);
        }
    }
}

void NGCustomUnitControl::_playJingleBeep() {
    if (_jingleBeep != NOJINGLE) {
        _playJingle(_jingleBeep);
    }
}

void NGCustomUnitControl::_playJingleAlarm() {
    if (_jingleAlarm != NOJINGLE) {
        _playJingle(_jingleAlarm);
    }
}

void NGCustomUnitControl::_initializeSplash() {
    if (_splash != nullptr) {
        _splash->setLogging(_logging);
        _splash->initialize();
    }
}

void NGCustomUnitControl::_initializeSoundMachine() {
    if (_soundMachine != nullptr) {
        _soundMachine->initialize();
    }
}

void NGCustomUnitControl::_initializeRTC() {
    if (_rtc != nullptr && _rtcInitialize) {
        _rtc->initialize(_rtcAdjust);
    }
}

void NGCustomUnitControl::_initializeKeypad() {
    if (_keypad != nullptr) {
        _keypad->initialize();
    }
}

void NGCustomUnitControl::_playJingle(byte jingle) {
    if (_soundMachine != nullptr) {
        _soundMachine->play(jingle);
    }
}

void NGCustomUnitControl::_runSplash() {
    #ifdef NG_PLATFORM_MEGA
    if (_logging) {
        writeInfo("Splash started...");
    }
    #endif
    while(!_splash->isFinished()) {
        _splash->processingLoop();
    }
    #ifdef NG_PLATFORM_MEGA
    if (_logging) {
        writeInfo("Splash finished");
    }
    #endif
}

void NGCustomUnitControl::initialize() {
    if (_pinStartup != NOSTARTUPPIN) {
        pinMode(_pinStartup, INPUT_PULLUP);
    }
    _initializeSplash();
    _initializeSoundMachine();
    _initializeRTC();
    _initializeKeypad();
    _playJingleBoot();
}

char* NGCustomUnitControl::getName() {
    return _name;
}

long int NGCustomUnitControl::startUp() {
    if (_splash != nullptr) {
        _runSplash();
    }
    _writeState();
    if (_logging) {
        observeMemory(0);
    }
    if (_pinStartup != NOSTARTUPPIN) {
        while(digitalRead(_pinStartup)) {
            _processingStartupLoop();
        }
    }
    long int res = millis();
    _playJingleStartup();
    return res;
}

void NGCustomUnitControl::processingLoop() {
    if (_keypad != nullptr) {
        _keypad->processingLoop();
    }
    if (_irremotedataReceived) {
        _processingIRRemoteData();
        _irremotedataReceived = false;
    }
}

void NGCustomUnitControl::setLogging(bool logging) {
    _logging = logging;
}

bool NGCustomUnitControl::getLogging() {
    return _logging;
}

void NGCustomUnitControl::setWorkMode(workMode workmode) {
    if (_workMode != workmode) {
        _workMode = workmode;
        _writeState();
    }
}

workMode NGCustomUnitControl::getWorkMode() {
    return _workMode;
}

void NGCustomUnitControl::registerSplash(NGSplash *splash) {
    _splash = splash;
}

void NGCustomUnitControl::registerStartup(NGCustomJingle *jingle) {
    registerStartup(NOSTARTUPPIN, jingle, DEFSTARTUPLOOPSCOUNT);
}

void NGCustomUnitControl::registerStartup(NGCustomJingle *jingle, int loops) {
    registerStartup(NOSTARTUPPIN, jingle, loops);
}

void NGCustomUnitControl::registerStartup(int pinStartup) {
    registerStartup(pinStartup, nullptr);
}

void NGCustomUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle) {
    registerStartup(pinStartup, jingle, DEFSTARTUPLOOPSCOUNT);
}

void NGCustomUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle, int loops) {
    _pinStartup = pinStartup;
    if (jingle != nullptr) {
        _jingleStartup = _registerJingle(jingle);
    }
    _jingleStartupLoops = loops;
}

void NGCustomUnitControl::registerBoot(NGCustomJingle *jingle) {
    _jingleBoot = _registerJingle(jingle);
}

void NGCustomUnitControl::registerBeep(NGCustomJingle *jingle) {
    _jingleBeep = _registerJingle(jingle);
}

void NGCustomUnitControl::registerJingleAlarm(NGCustomJingle *jingle) {
    _jingleAlarm = _registerJingle(jingle);
}

void NGCustomUnitControl::registerIRRemoteFunction(functionType type, byte protocol, byte address, byte command) {
    registerIRRemoteFunction(DEFIRREMOTE, type, protocol, address, command);
}

void NGCustomUnitControl::registerIRRemoteFunction(byte remote, functionType type, byte protocol, byte address, byte command) {
    if (_irremotefuncCount < IRFUNCCOUNT) {
        irremotefunc func;
        func.remote = remote;
        func.protocol = protocol;
        func.address = address;
        func.command = command;
        func.type = type;
        _irremotefunc[_irremotefuncCount] = func;
        _irremotefuncCount++;
    } else {
        _raiseException(ExceptionTooMuchIRFuncCount);
    }
}

void NGCustomUnitControl::registerRealTimeClock(NGRealTimeClock *rtc) {
    registerRealTimeClock(rtc, false);
}

void NGCustomUnitControl::registerRealTimeClock(NGRealTimeClock *rtc, bool initialize) {
    registerRealTimeClock(rtc, initialize, false);
}
    
void NGCustomUnitControl::registerRealTimeClock(NGRealTimeClock *rtc, bool initialize, bool adjust) {
    _rtc = rtc;
    _rtcInitialize = initialize;
    _rtcAdjust = adjust;
    #ifdef NG_PLATFORM_MEGA
    char log[100];
    sprintf(log, "RTC registered");
    writeInfo(log);
    #endif
}

void NGCustomUnitControl::registerKeypad(NGSimpleKeypad *keypad) {
    _keypad = keypad;
    #ifdef NG_PLATFORM_MEGA
    char log[100];
    sprintf(log, "Keypad registered");
    writeInfo(log);
    #endif
}

void NGCustomUnitControl::registerNotification(NGINotification *notification) {
    if (_notificationCount < NOTIFICATIONCOUNT) {
        char log[100];
        _notification[_notificationCount] = notification;
        _notification[_notificationCount]->initialize();
        _notificationCount++;
        sprintf(log, "%s registered", _notification[_notificationCount - 1]->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionTooMuchNotificationCount);
    }    
}

void NGCustomUnitControl::receiveDataStart() {
    _receivingData = true;
    _receivedDataCount = 0;
}

void NGCustomUnitControl::receivedData(int index, byte data) {
    _receivedData[index] = data;
}

void NGCustomUnitControl::receiveDataFinish(int count) {
    _receivingData = false;
    _receivedDataCount = count;
}

void NGCustomUnitControl::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(0);
    }
}

void NGCustomUnitControl::writeInfo(char* info) {
    writeInfo(info, 0);
}

void NGCustomUnitControl::writeInfo(char* info, int threshold) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(info, 0, 0);
    }
    if (delay > 0) {
        delay(threshold);
    }
}

void NGCustomUnitControl::beep() {
    _playJingleBeep();
}

void NGCustomUnitControl::setIRRemoteData(byte protocol, byte address, byte command) {
    setIRRemoteData(DEFIRREMOTE, protocol, address, command);
}

void NGCustomUnitControl::setIRRemoteData(byte remote, byte protocol, byte address, byte command) {
    if (!_irremotedataReceived) {
        _irremotedata.remote = remote;
        _irremotedata.protocol = protocol;
        _irremotedata.address = address;
        _irremotedata.command = command;
        _irremotedataReceived = true;
    }
}
