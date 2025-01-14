//
//  NGMulti7SegmentDisplay.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 24.03.24.
//

#ifndef NGMulti7SegmentDisplay_h
#define NGMulti7SegmentDisplay_h

#include <Arduino.h>
#include <NG7SegmentDisplay.h>

class NGMulti7SegmentDisplay {

private:
    NG7SegmentDisplay *_digit;
    byte _digitcount;
    int _value = 0;
    
protected:
    void _create(byte latchPin, byte clockPin, byte dataPin, byte digitcount);
    
    int _getBaseFromMode();
    
public:
    NGMulti7SegmentDisplay(byte latchPin, byte clockPin, byte dataPin, byte digitcount);
    
    void initialize();
    
    void setMode(sevenSegmentMode mode);
    
    void setValue(int value);
    
    void incrementValue();
    
    void decrementValue();
};

#endif /* NGMulti7SegmentDisplay_h */
