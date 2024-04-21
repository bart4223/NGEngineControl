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
            _value = '0';
            break;
        case 0x01:
            _value = '1';
            break;
        case 0x02:
            _value = '2';
            break;
        case 0x03:
            _value = '3';
            break;
        case 0x04:
            _value = '4';
            break;
        case 0x05:
            _value = '5';
            break;
        case 0x06:
            _value = '6';
            break;
        case 0x07:
            _value = '7';
            break;
        case 0x08:
            _value = '8';
            break;
        case 0x09:
            _value = '9';
            break;
    }
}
