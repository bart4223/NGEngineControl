//
//  NGColorDotMatrixBinaryClock.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#ifndef NGColorDotMatrixBinaryClock_h
#define NGColorDotMatrixBinaryClock_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGRealTimeClock.h>
#include "NGColorDotMatrixBinaryDigit.h"

#define DEFBINARYCLOCKDELAY 500

#define DEFBINARYCLOCKPOSX 1
#define DEFBINARYCLOCKPOSY 5

#define DIGITCOUNT 6

class NGColorDotMatrixBinaryClock {
   
private:
    NGColorDotMatrix *_cdm;
    NGRealTimeClock *_rtc;
    NGColorDotMatrixBinaryDigit *_digits[DIGITCOUNT];

protected:
    void _create(NGColorDotMatrix *cdm, byte posX, byte posY);
    
public:
    NGColorDotMatrixBinaryClock(NGColorDotMatrix *cdm);
    
    NGColorDotMatrixBinaryClock(NGColorDotMatrix *cdm, byte posX, byte posY);
    
    void initialize();
    
    void setColorOff(colorRGB color);

    void setColorOn(colorRGB color);
    
    void processingLoop();
};

#endif /* NGColorDotMatrixBinaryClock_h */
