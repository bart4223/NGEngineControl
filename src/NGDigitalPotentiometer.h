//
//  NGDigitalPotentiometer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.10.24.
//

#ifndef NGDigitalPotentiometer_h
#define NGDigitalPotentiometer_h

// MCP 4151
// PIN 1 = SS/CS  Uno = 10, Mega = 53
// PIN 2 = SCK    Uno = 13, Mega = 52
// PIN 3 = MOSI   Uno = 11, Mega = 51
// PIN 4 = GND
// PIN 5 = HIGH(5V)
// PIN 6 = 0 => LOW, 255 => HIGH
// PIN 7 = LOW(GND)
// PIN 8 = 5V

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFADDRESS  0x00
#define DEFMINVALUE    0
#define DEFMAXVALUE  255
#define DEFSTEPVALUE  10

enum digitalPotentiometerDirection { dpdUp, dpdDown };

class NGDigitalPotentiometer {
    
private:
    byte _address = DEFADDRESS;
    byte _pinCS;
    byte _minValue = DEFMINVALUE;
    byte _maxValue = DEFMAXVALUE;
    byte _stepValue = DEFSTEPVALUE;
    byte _value = 0xFF;
    digitalPotentiometerDirection _direction = dpdUp;

protected:
    void _create(byte pincs, byte address);
    
public:
    NGDigitalPotentiometer(byte pincs, byte address);
    
    void initialize();
    
    void initialize(byte initvalue);
    
    void setMinValue(byte minvalue);
    
    void setMaxValue(byte maxvalue);
    
    void setStepValue(byte stepvalue);
    
    void setValue(byte value);
    
    byte getValue();
    
    void incrementValue();
    
    void decrementValue();
    
    void changeValue();
};

#endif /* NGDigitalPotentiometer_h */
