//
//  NGStrings.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "NGStrings.h"

char* FloatToChar(float value) {
    _NGstr = String(value);
    return _NGstr.c_str();
}
