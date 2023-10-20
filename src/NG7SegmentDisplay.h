//
//  NG7SegmentDisplay.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#ifndef NG7SegmentDisplay_h
#define NG7SegmentDisplay_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NG8BitShiftRegister.h"

enum sevenSegmentMode { ssmDec, ssmHex };

class NG7SegmentDisplay {

private:
    sevenSegmentMode _mode = ssmDec;
    byte _value;
    NG8BitShiftRegister *_shiftRegister;
    
protected:
    void _create(byte latchPin, byte clockPin, byte dataPin);
    
    byte _getThreshold();
    
public:
    NG7SegmentDisplay(byte latchPin, byte clockPin, byte dataPin);
    
    void initialize();
    
    void setMode(sevenSegmentMode mode);
    
    void setValue(byte value);
    
    byte getValue();
    
    void incrementValue();
    
    void decrementValue();
    
    void setDot();
    
    void resetDot();
};

#endif /* NG7SegmentDisplay_h */
