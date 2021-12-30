//
//  NGStrings.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "NGStrings.h"

char* FloatToChar(float value) {
    String s = String(value);
    char *res = malloc(s.length() + 1);
    s.getBytes(res, s.length() + 1);
    return res;
}

char* LeftPadInteger(int value, int digits) {
    String s = String(value);
    int count  = digits - s.length();
    for (int i = count; i > 0; i--) {
        s = "0" + s;
    }
    char *res = malloc(s.length() + 1);
    s.getBytes(res, s.length() + 1);
    return res;
}
