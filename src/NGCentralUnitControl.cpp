//
//  NGCentralUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#include "NGCommon.h"
#include "NGCentralUnitControl.h"

NGCentralUnitControl::NGCentralUnitControl() {
    _create(NONAME, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name) {
    _create(name, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name, int serialRate) {
    _create(name, serialRate);
}

void NGCentralUnitControl::initialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" initialized", _name);
        _writeInfo(log);
    }
}
