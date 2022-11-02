//
//  NGBinaryClockUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#ifndef NGBinaryClockUnitControl_h
#define NGBinaryClockUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGColorDotMatrixBinaryDigit.h"
#include <NGCustomUnitControl.h>

#define _VERSION "0.1"
#define VERSION (char*)_VERSION

#define DEFBINARYCLOCKPOSX 1
#define DEFBINARYCLOCKPOSY 5

#define DIGITCOUNT 6

class NGBinaryClockUnitControl : public NGCustomUnitControl {
    
private:
    NGColorDotMatrix *_cdm;
    NGColorDotMatrixBinaryDigit *_digits[DIGITCOUNT];
    
protected:
    void _create(char* name, byte address, int serialRate, NGColorDotMatrix *cdm, byte posX, byte posY);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
    void _processingClock();
public:
    NGBinaryClockUnitControl(char* name, NGColorDotMatrix *cdm);
    
    NGBinaryClockUnitControl(char* name, NGColorDotMatrix *cdm, byte posX, byte posY);
    
    void initialize();
    
    void setColorOff(colorRGB color);
    
    void setColorOn(colorRGB color);
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGBinaryClockUnitControl_h */
