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

static String _NGstr;

char* FloatToChar(float value);

#endif /* NGStrings_h */
