//
//  NGColorDotMatrixDecimalDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 02.03.23.
//

#include "NGColorDotMatrixDecimalDigit.h"

NGColorDotMatrixDecimalDigit::NGColorDotMatrixDecimalDigit(NGIPaintableComponent *ipc) {
    _create(ipc, 0, 0);
}

void NGColorDotMatrixDecimalDigit::setValue(byte value) {
    switch(value) {
        case 0x00:
            setChar('0');
            break;
        case 0x01:
            setChar('1');
            break;
        case 0x02:
            setChar('2');
            break;
        case 0x03:
            setChar('3');
            break;
        case 0x04:
            setChar('4');
            break;
        case 0x05:
            setChar('5');
            break;
        case 0x06:
            setChar('6');
            break;
        case 0x07:
            setChar('7');
            break;
        case 0x08:
            setChar('8');
            break;
        case 0x09:
            setChar('9');
            break;
    }
}
