//
//  NG7SegmentDisplay.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#ifndef NG7SegmentDisplay_h
#define NG7SegmentDisplay_h

#include <Arduino.h>
#include <Misc/NG8BitShiftRegister.h>

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
    
    sevenSegmentMode getMode();
    
    void setValue(byte value);
    
    byte getValue();
    
    void incrementValue();
    
    void decrementValue();
    
    void setDot();
    
    void resetDot();
    
    void beginUpdate();
    
    void endUpdate();
};

#endif /* NG7SegmentDisplay_h */
