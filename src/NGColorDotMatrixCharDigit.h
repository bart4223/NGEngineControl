//
//  NGColorDotMatrixCharDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.04.24.
//

#ifndef NGColorDotMatrixCharDigit_h
#define NGColorDotMatrixCharDigit_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGColorDotMatrixCustomDigit.h"

class NGColorDotMatrixCharDigit : public NGColorDotMatrixCustomDigit {
    
public:
    NGColorDotMatrixCharDigit(NGIPaintableComponent *ipc);
};

#endif /* NGColorDotMatrixCharDigit_h */
