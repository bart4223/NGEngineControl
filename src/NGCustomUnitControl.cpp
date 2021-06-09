//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
#include "NGCustomUnitControl.h"

void NGCustomUnitControl::_create(char* name, int serialRate) {
    _name = name;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
}

void NGCustomUnitControl::initialize() {
    
}
