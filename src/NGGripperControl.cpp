//
//  NGGripperControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.05.21.
//

#include "NGGripperControl.h"

NGGripperControl::NGGripperControl() {
    
}

NGGripperControl::NGGripperControl(int engine) {
    _create(engine, DEFAULTSERIALRATE);
}

NGGripperControl::NGGripperControl(int engine, int serialRate) {
    _create(engine, serialRate);
}

void NGGripperControl::_create(int engine, int serialRate) {
    _engine = engine;
    _initialized = false;
    _logging = true;
    _engine = NGEngineControl(engine, serialRate);
    _engine.setLogging(_logging);
}

void NGGripperControl::initialize(int minSpeed, int maxSpeed) {
    char log[100];
    _engine.initialize();
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
    if (_logging) {
        sprintf(log, "Start initialization of NGGripperControl with engine %d...", _engine);
        Serial.println(log);
    }
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGGripperControl with engine %d successfully initialized", _engine);
        Serial.println(log);
    }
}

void NGGripperControl::grip() {
    _engine.setSpeed(_maxSpeed);
    _engine.run(edForward);
    delay(900);
    _engine.setSpeed(_minSpeed);
    delay(3000);
    _engine.stop();
}

void NGGripperControl::release() {
    _engine.setSpeed(_maxSpeed);
    _engine.run(edBackward);
    delay(900);
    _engine.setSpeed(_minSpeed);
    delay(1600);
    _engine.stop();
}
