//
//  NGColorDotMatrixCharDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.04.24.
//

#ifndef NGColorDotMatrixCharDigit_h
#define NGColorDotMatrixCharDigit_h

#include <Arduino.h>
#include <NGColorDotMatrixCustomDigit.h>

class NGColorDotMatrixCharDigit : public NGColorDotMatrixCustomDigit {
    
public:
    NGColorDotMatrixCharDigit(NGIPaintableComponent *ipc);
};

#endif /* NGColorDotMatrixCharDigit_h */
