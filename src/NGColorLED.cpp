//
//  NGColorLED.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.07.24.
//

#include "NGColorLED.h"

NGColorLED::NGColorLED(byte pinRed, byte pinGreen, byte pinBlue) {
    _create(pinRed, pinGreen, pinBlue);
}

void NGColorLED::_create(byte pinRed, byte pinGreen, byte pinBlue) {
    _pinRed = pinRed;
    _pinGreen = pinGreen;
    _pinBlue = pinBlue;
}

void NGColorLED::_render() {
    analogWrite(_pinRed, _color.red);
    analogWrite(_pinGreen, _color.green);
    analogWrite(_pinBlue, _color.blue);
}

void NGColorLED::initialize() {
    initialize(COLOR_BLACK);
}

void NGColorLED::initialize(colorRGB color) {
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinGreen, OUTPUT);
    pinMode(_pinBlue, OUTPUT);
    setColor(color);
}

void NGColorLED::setColor(colorRGB color) {
    _color = color;
    _render();
}
