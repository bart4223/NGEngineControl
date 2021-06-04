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
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
    if (_logging) {
        sprintf(log, "Start initialization of NGGripperControl with engine %d...", _engine);
        Serial.println(log);
    }
    _engine.initialize();
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGGripperControl with engine %d successfully initialized", _engine);
        Serial.println(log);
    }
}

void NGGripperControl::grip() {
    grip(DEFAULTGRIPDELAYONE, DEFAULTGRIPDELAYTWO);
}

void NGGripperControl::grip(unsigned long delayOne, unsigned long delayTwo) {
    _engine.setSpeed(_maxSpeed);
    _engine.run(edForward);
    delay(delayOne);
    _engine.setSpeed(_minSpeed);
    delay(delayTwo);
    _engine.stop();
}
void NGGripperControl::release() {
    release(DEFAULTRELEASEDELAYONE, DEFAULTRELEASEDELAYTWO);
}
                               
void NGGripperControl::release(unsigned long delayOne, unsigned long delayTwo) {
    _engine.setSpeed(_maxSpeed);
    _engine.run(edBackward);
    delay(delayOne);
    _engine.setSpeed(_minSpeed);
    delay(delayTwo);
    _engine.stop();
}
