//
//  NGCustomDataStorage.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.11.22.
//

#include "NGCustomDataStorage.h"

void NGCustomDataStorage::setLogging(bool logging) {
    _logging = logging;
}

bool NGCustomDataStorage::getLogging() {
    return _logging;
}
