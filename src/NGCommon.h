//
//  NGCommon.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#ifndef NGCommon_h
#define NGCommon_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFAULTSERIALRATE   9600
#define NONAME              (char*)""

static bool _globalSerialStarted = false;

void _ensureGlobalSerial(int serialRate);

#endif /* NGCommon_h */
