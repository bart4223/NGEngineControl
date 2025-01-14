//
//  NGColorLED.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.07.24.
//

#ifndef NGColorLED_h
#define NGColorLED_h

#include <Arduino.h>
#include <NGCommonGraphics.h>

class NGColorLED {
    
private:
    byte _pinRed;
    byte _pinGreen;
    byte _pinBlue;
    colorRGB _color;

protected:
    void _create(byte pinRed, byte pinGreen, byte pinBlue);
    void _render();
    
public:
    NGColorLED(byte pinRed, byte pinGreen, byte pinBlue);
    
    void initialize();
    
    void initialize(colorRGB color);
    
    void setColor(colorRGB color);
};

#endif /* NGColorLED_h */
