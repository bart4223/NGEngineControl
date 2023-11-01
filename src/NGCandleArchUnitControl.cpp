//
//  NGCandleArchUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGExceptionDefinitions.h"
#include "NGMemoryObserver.h"
#include "NGCandleArchUnitControl.h"

NGCandleArchUnitControl::NGCandleArchUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGCandleArchUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

byte NGCandleArchUnitControl::_registerScenario(candleArchLightingScenarioKind kind, byte thresholdid) {
    byte res = _lightingScenarioCount;
    if (_lightingScenarioCount < MAXSCENARIOCOUNT) {
        candleArchLightingScenario cals;
        cals.kind = kind;
        cals.thresholdid = thresholdid;
        _lightingScenarios[_lightingScenarioCount] = cals;
        _lightingScenarioCount++;
    } else {
        _raiseException(ExceptionTooMuchLightingScenarioCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Scenario %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGCandleArchUnitControl::_processingReceivedData() {
    
}

void NGCandleArchUnitControl::_processingStartupLoop() {

}

void NGCandleArchUnitControl::_processingIRRemoteData() {
    
}

void NGCandleArchUnitControl::_beginAllAreaUpdate() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->beginUpdate();
    }
}

void NGCandleArchUnitControl::_endAllAreaUpdate() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->endUpdate();
    }
}

byte NGCandleArchUnitControl::registerLightingArea(byte switcherLatchPin, byte switcherClockPin, byte switcherDataPin) {
    byte res = _lightingAreaCount;
    if (_lightingAreaCount < MAXLIGHTINGAREACOUNT) {
        candleArchLightingArea cala;
        cala.switcher = new NG8BitShiftRegister(switcherLatchPin, switcherClockPin, switcherDataPin);
        cala.lightscount = 0;
        _lightingAreas[_lightingAreaCount] = cala;
        _lightingAreaCount++;
    } else {
        _raiseException(ExceptionTooMuchLightingAreaCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Lighting area %d registered", res);
        writeInfo(log);
    }
    return res;
}

byte NGCandleArchUnitControl::registerLight(byte area) {
    byte res;
    if (area >= 0 && area < _lightingAreaCount) {
        if (_lightingAreas[area].lightscount < MAXLIGHTSCOUNT) {
            res = _lightingAreas[area].lightscount;
            byte value = 1;
            _lightingAreas[area].lights[_lightingAreas[area].lightscount] = value << _lightingAreas[area].lightscount;
            _lightingAreas[area].lightscount++;
        } else {
            _raiseException(ExceptionTooMuchLightingAreaLightCount);
        }
    } else {
        _raiseException(ExceptionInvalidLightingArea);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Light %d/%d registered", area, res);
        writeInfo(log);
    }
    return res;
}

byte NGCandleArchUnitControl::registerScenario() {
    return _registerScenario(calskNone, 0);
}

byte NGCandleArchUnitControl::registerLightSensorScenario(byte thresholdid) {
    return _registerScenario(calskLightSensor, thresholdid);
}

byte NGCandleArchUnitControl::registerScenarioArea(byte scenario, byte area) {
    byte res = 0;
    if (scenario >= 0 && scenario < _lightingScenarioCount) {
        res = _lightingScenarios[scenario].areacount;
        if (_lightingScenarios[scenario].areacount < MAXLIGHTINGAREACOUNT) {
            candleArchLightingScenarioArea calsa;
            calsa.area = area;
            _lightingScenarios[scenario].areas[_lightingScenarios[scenario].areacount] = calsa;
            _lightingScenarios[scenario].areacount++;
        } else {
            _raiseException(ExceptionTooMuchLightingScenarioAreaCount);
        }
        if (_logging) {
            char log[100];
            sprintf(log, "Scenario Area %d/%d registered", scenario, res);
            writeInfo(log);
        }
    }
    return res;
}

byte NGCandleArchUnitControl::registerScenarioAreaLight(byte scenario, byte scenarioarea, byte light) {
    byte res = 0;
    if (scenario >= 0 && scenario < _lightingScenarioCount) {
        if (scenarioarea >= 0 && scenarioarea < _lightingScenarios[scenario].areacount) {
            res = _lightingScenarios[scenario].areas[scenarioarea].lightscount;
            if (_lightingScenarios[scenario].areas[scenarioarea].lightscount < MAXLIGHTSCOUNT) {
                _lightingScenarios[scenario].areas[scenarioarea].lights[_lightingScenarios[scenario].areas[scenarioarea].lightscount] = light;
                _lightingScenarios[scenario].areas[scenarioarea].lightscount++;
            } else {
                _raiseException(ExceptionTooMuchLightingScenarioAreaLightCount);
            }
            if (_logging) {
                char log[100];
                sprintf(log, "Scenario Area Light %d/%d/%d registered", scenario, scenarioarea, res);
                writeInfo(log);
            }
        }
    }
    return res;
}

void NGCandleArchUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->initialize();
        _lightingAreas[i].switcher->setValue(0);
    }
}

void NGCandleArchUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (_processLightSensorThresholdId) {
        _processLightSensorThresholdId = false;
        for (int i = 0; i < _lightingScenarioCount; i++) {
            if (_lightingScenarios[i].kind == calskLightSensor) {
                if (_lightingScenarios[i].thresholdid == _lastLightSensorThresholdId) {
                    activateScenario(i);
                }
            }
        }
    }
}

void NGCandleArchUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGCandleArchUnitControl::testSequenceStart() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->setValue(255);
    }
}

void NGCandleArchUnitControl::testSequenceStop() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->setValue(0);
    }
}

void NGCandleArchUnitControl::switchLight(byte area, byte light, bool on) {
    if (area >= 0 && area < _lightingAreaCount) {
        if (light >= 0 && light < _lightingAreas[area].lightscount) {
            if (on) {
                if ((_lightingAreas[area].switcher->getValue() & _lightingAreas[area].lights[light]) == 0) {
                    _lightingAreas[area].switcher->setValue(_lightingAreas[area].switcher->getValue() + _lightingAreas[area].lights[light]);
                    if (_logging) {
                        char log[100];
                        sprintf(log, "Light %d/%d on", area, light);
                        writeInfo(log);
                    }
                }
            } else {
                if ((_lightingAreas[area].switcher->getValue() & _lightingAreas[area].lights[light]) != 0) {
                    _lightingAreas[area].switcher->setValue(_lightingAreas[area].switcher->getValue() - _lightingAreas[area].lights[light]);
                    if (_logging) {
                        char log[100];
                        sprintf(log, "Light %d/%d off", area, light);
                        writeInfo(log);
                    }
                }
            }
        } else {
            _raiseException(ExceptionInvalidLightingLight);
        }
    } else {
        _raiseException(ExceptionInvalidLightingArea);
    }
}

void NGCandleArchUnitControl::switchAllLights(bool on) {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->beginUpdate();
        for (int j = 0; j < _lightingAreas[i].lightscount; j++) {
            switchLight(i, j, on);
        }
        _lightingAreas[i].switcher->endUpdate();
    }
}

void NGCandleArchUnitControl::activateScenario(int scenario) {
    if (scenario != _activeScenario) {
        _activeScenario = scenario;
        if (scenario != NOACTIVESCENARIO) {
            if (_activeScenario >= 0 && _activeScenario < _lightingScenarioCount) {
                _beginAllAreaUpdate();
                switchAllLights(false);
                for (int i = 0; i < _lightingScenarios[_activeScenario].areacount; i++) {
                    _lightingAreas[_lightingScenarios[_activeScenario].areas[i].area].switcher->beginUpdate();
                    for (int j = 0; j < _lightingScenarios[_activeScenario].areas[i].lightscount; j++) {
                        switchLight(_lightingScenarios[_activeScenario].areas[i].area, _lightingScenarios[_activeScenario].areas[i].lights[j], true);
                    }
                    _lightingAreas[_lightingScenarios[_activeScenario].areas[i].area].switcher->endUpdate();
                }
                _endAllAreaUpdate();
            }
        } else {
            switchAllLights(false);
        }
    }
}

void NGCandleArchUnitControl::activateFirstScenario() {
    if (_lightingScenarioCount > 0) {
        activateScenario(0);
    }
}

void NGCandleArchUnitControl::activateNoScenario() {
    activateScenario(NOACTIVESCENARIO);
}

bool NGCandleArchUnitControl::isLightOn(byte area, byte light) {
    bool res;
    if (area >= 0 && area < _lightingAreaCount) {
        if (light >= 0 && light < _lightingAreas[area].lightscount) {
            res = (_lightingAreas[area].switcher->getValue() & _lightingAreas[area].lights[light]) != 0;
        } else {
            _raiseException(ExceptionInvalidLightingLight);
        }
    } else {
        _raiseException(ExceptionInvalidLightingArea);
    }
    return res;
}

void NGCandleArchUnitControl::toogleLight(byte area, byte light) {
    switchLight(area, light, !isLightOn(area, light));
}

void NGCandleArchUnitControl::setLightSensorData(byte id) {
    if (_lastLightSensorThresholdId != id) {
        _lastLightSensorThresholdId = id;
        _processLightSensorThresholdId = true;
    }
}
