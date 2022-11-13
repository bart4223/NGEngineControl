//
//  NGSDDataStorage.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.11.22.
//

#include <SPI.h>
//#include <SD.h>
#include "NGSDDataStorage.h"

NGSDDataStorage::NGSDDataStorage() {
    _create(DEFSDCSPIN);
}

NGSDDataStorage::NGSDDataStorage(byte pinCS) {
    _create(pinCS);
}

void NGSDDataStorage::_create(byte pinCS) {
    _pinCS = pinCS;
}

void NGSDDataStorage::initialize() {
    if (!_initialized) {
        //_initialized = SD.begin(_pinCS);
        if (_logging) {
            if (_initialized) {
                Serial.println("SD Card initialized");
            } else {
                Serial.println("SD Card not initialized");
            }
        }
    }
}

void NGSDDataStorage::open() {
    
}

void NGSDDataStorage::close() {
    
}
