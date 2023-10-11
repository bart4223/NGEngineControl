//
//  NGAnchormanUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.23.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGExceptionDefinitions.h"
#include "NGMemoryObserver.h"
#include "NGAnchormanUnitControl.h"

NGAnchormanUnitControl::NGAnchormanUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGAnchormanUnitControl::NGAnchormanUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGAnchormanUnitControl::NGAnchormanUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGAnchormanUnitControl::NGAnchormanUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGAnchormanUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGAnchormanUnitControl::_processingReceivedData() {
    
}

void NGAnchormanUnitControl::_processingStartupLoop() {

}

void NGAnchormanUnitControl::_processingIRRemoteData() {
    
}

byte NGAnchormanUnitControl::registerSimpleTurnTableMotionProfile(long stepForwardRun, long stepForwardStop, long stepBackwardRun, long stepBackwardStop) {
    byte res = _turnTableMotionProfileCount;
    if (_turnTableMotionProfileCount < MAXTURNTABLEMOTIONPROFILECOUNT) {
        turnTableMotionProfile ttmp;
        ttmp.kind = ttmpkSimple;
        ttmp.steps[0] = stepForwardRun;
        ttmp.steps[1] = stepForwardStop;
        ttmp.steps[2] = stepBackwardRun;
        ttmp.steps[3] = stepBackwardStop;
        ttmp.count = 4;
        _turnTableMotionProfiles[_turnTableMotionProfileCount] = ttmp;
        _turnTableMotionProfileCount++;
    } else {
        _raiseException(ExceptionTooMuchTurnTableMotionProfileCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "MotionProfile %d registered", res);
        writeInfo(log);
    }
    return res;
}

byte NGAnchormanUnitControl::registerTurnTable(NGEngineControl* engine, byte speed, int delay, int profile) {
    byte res = _turnTableCount;
    if (_turnTableCount < MAXTURNTABLECOUNT) {
        turnTable tt;
        tt.engine = engine;
        tt.speed = speed;
        tt.delay = delay;
        tt.profile = profile;
        _turnTables[_turnTableCount] = tt;
        _turnTableCount++;
    } else {
        _raiseException(ExceptionTooMuchTurnTableCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "TurnTable %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGAnchormanUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _turnTableCount; i++) {
        _turnTables[i].engine->initialize();
        _turnTables[i].engine->setSpeed(_turnTables[i].speed, _turnTables[i].delay);
        _turnTables[i].engine->setLogging(_logging);
        _turnTables[i].currentstep = NOTURNTABLECURRENTSTEP;
        _turnTables[i].laststep = millis();
    }
}

void NGAnchormanUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    for (int i = 0; i < _turnTableCount; i++) {
        if (_turnTables[i].profile > NOTURNTABLEMOTIONPROFILE) {
            turnTableMotionProfile ttmp = _turnTableMotionProfiles[_turnTables[i].profile];
            bool nextStep = _turnTables[i].currentstep == NOTURNTABLECURRENTSTEP;
            if (!nextStep) {
                nextStep = (millis() - _turnTables[i].laststep) > ttmp.steps[_turnTables[i].currentstep];
            }
            if (nextStep) {
                _turnTables[i].currentstep++;
                if (_turnTables[i].currentstep == ttmp.count) {
                    _turnTables[i].currentstep = 0;
                }
                char log[100];
                sprintf(log, "Step %d", _turnTables[i].currentstep);
                clearInfo();
                writeInfo(log);
                _turnTables[i].laststep = millis();
                switch(ttmp.kind) {
                    case ttmpkSimple:
                        switch(_turnTables[i].currentstep) {
                            case 0:
                                _turnTables[i].engine->run(edForward);
                                break;
                            case 1:
                                _turnTables[i].engine->stop();
                                break;
                            case 2:
                                _turnTables[i].engine->run(edBackward);
                                break;
                            case 3:
                                _turnTables[i].engine->stop();
                                break;
                        }
                        break;
                }
            }
        }
    }
}

void NGAnchormanUnitControl::incrementMotionProfileStep(byte profile, byte step, int count) {
    if (profile >= 0 && profile < _turnTableMotionProfileCount) {
        if (step >= 0 && step < _turnTableMotionProfiles[profile].count) {
            _turnTableMotionProfiles[profile].steps[step] = _turnTableMotionProfiles[profile].steps[step] + count;
        }
    }
}

void NGAnchormanUnitControl::decrementMotionProfileStep(byte profile, byte step, int count) {
    if (profile >= 0 && profile < _turnTableMotionProfileCount) {
        if (step >= 0 && step < _turnTableMotionProfiles[profile].count) {
            _turnTableMotionProfiles[profile].steps[step] = _turnTableMotionProfiles[profile].steps[step] - count;
            if (_turnTableMotionProfiles[profile].steps[step] < 0) {
                _turnTableMotionProfiles[profile].steps[step] = 0;
            }
        }
    }
}

void NGAnchormanUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
