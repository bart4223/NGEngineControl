//
//  NG4x4Keypad.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.02.24.
//

#ifndef NG4x4Keypad_h
#define NG4x4Keypad_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Keypad.h"

#define KEYPADROWS 4
#define KEYPADCOLS 4

typedef void (*FourxFourKeypadCallbackFunc)(char key);

class NG4x4Keypad {
    
private:
    Keypad *_keypad;
    char _keys[KEYPADROWS][KEYPADCOLS];
    byte _rowPins[KEYPADROWS];
    byte _colPins[KEYPADCOLS];
    FourxFourKeypadCallbackFunc _callback = nullptr;
    bool _logging = false;

protected:
    void _create(byte pinRow0, byte pinRow1, byte pinRow2, byte pinRow3, byte pinCol0, byte pinCol1, byte pinCol2, byte pinCol3);
    
public:
    NG4x4Keypad(byte pinRow0, byte pinRow1, byte pinRow2, byte pinRow3, byte pinCol0, byte pinCol1, byte pinCol2, byte pinCol3);
    
    void registerCallback(FourxFourKeypadCallbackFunc callback);
    
    void registerKey(byte row, byte col, char key);
    
    void setLogging(bool logging);
    
    void initialize();
    
    void processingLoop();
};

#endif /* NG4x4Keypad_h */
