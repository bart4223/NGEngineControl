//
//  NGStrings.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#ifndef NGStrings_h
#define NGStrings_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

char* FloatToChar(float value);

char* LeftPadInteger(int value, int digits);

#endif /* NGStrings_h */
