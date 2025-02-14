//
//  NGSimpleLED.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.02.25.
//

#include <NGSimpleLED.h>

NGSimpleLED::NGSimpleLED() {
    _create(DEFPINLED);
}

NGSimpleLED::NGSimpleLED(byte pinLED) {
    _create(pinLED);
}

void NGSimpleLED::_create(byte pinLED) {
    _pinLED = pinLED;
}

void NGSimpleLED::_switch(bool on) {
    _on = on;
    if (on) {
        digitalWrite(_pinLED, HIGH);    
    } else {
        digitalWrite(_pinLED, LOW);
    }
}

void NGSimpleLED::initialize() {
    pinMode(_pinLED, OUTPUT);
    off();
}

void NGSimpleLED::on() {
    _switch(true);
}

void NGSimpleLED::off() {
    _switch(false);
}

bool NGSimpleLED::isOn() {
    return _on;
}