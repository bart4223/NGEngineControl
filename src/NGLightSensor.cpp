//
//  NGLightSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.09.21.
//

#include "NGLightSensor.h"
#include "NGExceptionDefinitions.h"

NGLightSensor::NGLightSensor() {
    _create(DEFPINLIGHTSENSOR);
}

NGLightSensor::NGLightSensor(byte pinSensor) {
    _create(pinSensor);
}

void NGLightSensor::_create(byte pinSensor) {
    _pinSensor = pinSensor;
}

void NGLightSensor::_raiseException(int id) {
    char log[100];
    sprintf(log, "Exception %d", id);
    Serial.println(log);

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
    if (_thresholdCount < MAXTHRESHOLDCOUNT) {
        sensorThreshold st;
        st.actionKind = takPin;
        st.threshold = threshold;
        st.level = level;
        st.delay = delay;
        st.pin = pin;
        st.valence = valence;
        _thresholds[_thresholdCount] = st;
        _thresholdCount++;
    } else {
        _raiseException(ExceptionTooMuchLightSensorThresholdCount);
    }
}

void NGLightSensor::registerThreshold(int threshold, thresholdLevel level, byte id, lightSensorCallbackFunc callback) {
    registerThreshold(threshold, level, id, callback, DEFTHRESHOLDDELAY);
}

void NGLightSensor::registerThreshold(int threshold, thresholdLevel level, byte id, lightSensorCallbackFunc callback, int delay) {
    if (_thresholdCount < MAXTHRESHOLDCOUNT) {
        sensorThreshold st;
        st.actionKind = takCallback;
        st.threshold = threshold;
        st.level = level;
        st.delay = delay;
        st.id = id;
        st.callback = callback;
        _thresholds[_thresholdCount] = st;
        _thresholdCount++;
    } else {
        _raiseException(ExceptionTooMuchLightSensorThresholdCount);
    }
}

void NGLightSensor::setLogging(bool logging) {
    setLogging(logging, CDEFLOGDELAY);
}

void NGLightSensor::setLogging(bool logging, int logdelay) {
    _logging = logging;
    _logDelay = logdelay;
}

bool NGLightSensor::getLogging() {
    return _logging;
}

void NGLightSensor::determine() {
    int value = analogRead(_pinSensor);
    if (_logging) {
        if (millis() - _lastLog > _logDelay) {
            Serial.println(value);
            _lastLog = millis();
        }
    }
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
        if (millis() - _thresholds[i].lastAction > _thresholds[i].delay) {
            _thresholds[i].lastAction = millis();
            switch (_thresholds[i].actionKind) {
                case takPin:
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
                    break;
                case takCallback:
                    if (ok) {
                        if (_thresholds[i].callback != nullptr) {
                            _thresholds[i].callback(_thresholds[i].id);
                        }
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

void NGLightSensor::processingLoop() {
    determine();
}
