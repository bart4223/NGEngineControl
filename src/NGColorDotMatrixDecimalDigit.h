//
//  NGColorDotMatrixDecimalDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 02.03.23.
//

#ifndef NGColorDotMatrixDecimalDigit_h
#define NGColorDotMatrixDecimalDigit_h

#include <Arduino.h>
#include <NGColorDotMatrixCustomDigit.h>

class NGColorDotMatrixDecimalDigit : public NGColorDotMatrixCustomDigit {
    
public:
    NGColorDotMatrixDecimalDigit(NGIPaintableComponent *ipc);
    
    void setValue(byte value);
};

#endif /* NGColorDotMatrixDecimalDigit_h */
