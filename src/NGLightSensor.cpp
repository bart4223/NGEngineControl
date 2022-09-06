//
//  NGLightSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.09.21.
//

#include "NGLightSensor.h"

NGLightSensor::NGLightSensor() {
    _create(DEFPINLIGHTSENSOR);
}

NGLightSensor::NGLightSensor(byte pinSensor) {
    _create(pinSensor);
}

void NGLightSensor::_create(byte pinSensor) {
    _pinSensor = pinSensor;
}

void NGLightSensor::initialize() {
    for (int i = 0; i < _thresholdCount; i++) {
        pinMode(_thresholds[i].pin, OUTPUT);
        digitalWrite(_thresholds[i].pin, LOW);
    }
}

void NGLightSensor::registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence) {
    registerThreshold(threshold, level, pin, valence, DEFTHRESHOLDDELAY);
}

void NGLightSensor::registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay) {
    sensorThreshold st;
    st.threshold = threshold;
    st.level = level;
    st.pin = pin;
    st.valence = valence;
    st.delay = delay;
    st.counter = 0;
    _thresholds[_thresholdCount] = st;
    _thresholdCount++;
}

void NGLightSensor::determine() {
    int value = analogRead(_pinSensor);
    for (int i = 0; i < _thresholdCount; i++) {
        bool ok = false;
        switch (_thresholds[i].level) {
            case tlUnder:
                ok = value < _thresholds[i].threshold;
                break;
            case tlOver:
                ok = value > _thresholds[i].threshold;
                break;
        }
        if (_thresholds[i].counter == 0) {
            _thresholds[i].counter = _thresholds[i].delay;
        }
        if (_thresholds[i].counter > 0) {
            _thresholds[i].counter--;
        }
        if (_thresholds[i].counter == 0) {
            switch (_thresholds[i].valence) {
                case tvLow:
                    if (ok) {
                        digitalWrite(_thresholds[i].pin, LOW);
                    } else {
                        digitalWrite(_thresholds[i].pin, HIGH);
                    }
                    break;
                case tvHigh:
                    if (ok) {
                        digitalWrite(_thresholds[i].pin, HIGH);
                    } else {
                        digitalWrite(_thresholds[i].pin, LOW);
                    }
                    break;
            }
        }
    }
}

void NGLightSensor::testSequenceStart() {
    initialize();
    for (int i = 0; i < _thresholdCount; i++) {
        digitalWrite(_thresholds[i].pin, HIGH);
    }
}

void NGLightSensor::testSequenceStop() {
    for (int i = 0; i < _thresholdCount; i++) {
        digitalWrite(_thresholds[i].pin, LOW);
    }
}
