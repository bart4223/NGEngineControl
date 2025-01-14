//
//  NGBinaryClockUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#ifndef NGBinaryClockUnitControl_h
#define NGBinaryClockUnitControl_h

#include <Arduino.h>
#include <NGColorDotMatrixBinaryDigit.h>
#include <NGCustomUnitControl.h>

#define _VERSION "0.4"
#define VERSION (char*)_VERSION

#define DEFBINARYCLOCKPOSX 0
#define DEFBINARYCLOCKPOSY 5

#define DIGITCOUNT 6

class NGBinaryClockUnitControl : public NGCustomUnitControl {
    
private:
    NGIPaintableComponent *_cdm;
    NGColorDotMatrixBinaryDigit *_digits[DIGITCOUNT];
    bool _withArityOffset = true;
    bool _adjustRTC = false;
    
protected:
    void _create(char* name, byte address, int serialRate, NGIPaintableComponent *cdm, byte posX, byte posY);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
    void _processingClock();
public:
    NGBinaryClockUnitControl(char* name, NGIPaintableComponent *cdm);
    
    NGBinaryClockUnitControl(char* name, NGIPaintableComponent *cdm, byte posX, byte posY);
    
    void initialize();
    
    void setAdjustRTC(bool adjustRTC);
    
    void setColorOff(colorRGB color);
    
    void setColorOn(colorRGB color);
    
    void setOffset(int offsetX, int offsetY);

    void processingLoop();
    
    void requestData(byte* data);    
};

#endif /* NGBinaryClockUnitControl_h */
