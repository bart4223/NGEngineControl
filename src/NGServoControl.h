//
//  NGServoControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.22.
//

#ifndef NGServoControl_h
#define NGServoControl_h

#include <Arduino.h>
#include <Servo.h>

#define DEFSERVOPIN             8
#define DEFSERVOMINPOSITION     0
#define DEFSERVOZEROPOSITION    90
#define DEFSERVOMAXPOSITION     180
#define DEFSERVOSTEPWIDTH       10

class NGServoControl {

private:
    byte _pinServo = DEFSERVOPIN;
    Servo *_Servo;
    byte _position;
    byte _zeroPosition = DEFSERVOZEROPOSITION;
    byte _minPosition = DEFSERVOMINPOSITION;
    byte _maxPosition = DEFSERVOMAXPOSITION;
    byte _stepWidth = DEFSERVOSTEPWIDTH;
    bool _initialized;
    bool _logging;
    
protected:
    void _create(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition, byte stepWidth);

public:
    NGServoControl(byte pinServo);

    NGServoControl(byte pinServo, byte zeroPosition);

    NGServoControl(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition);

    NGServoControl(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition, byte stepWidth);

    void initialize();
       
    void setLogging(bool logging);
    
    bool getLogging();
    
    void setPosition(byte pos);

    byte getPosition();
    
    void reset();
    
    void stepUp();

    void stepDown();
    
    bool isMinPosition();
    
    bool isMaxPosition();
};

#endif /* NGServoControl_h */
