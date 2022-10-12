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

#ifdef ARDUINO_AVR_UNO
#define NG_PLATFORM_UNO
#elif ARDUINO_AVR_MEGA2560
#define NG_PLATFORM_MEGA
#elif ARDUINO_AVR_NANO
#define NG_PLATFORM_NANO
#endif

#define DEFAULTSERIALRATE   9600
#define NONAME              (char*)""

enum functionType { ftMenu, ftLeft, ftRight, ftUp, ftDown, ftOK, ftPlay };

static bool _globalSerialStarted = false;

void _ensureGlobalSerial(int serialRate);

bool getYesOrNo();

#endif /* NGCommon_h */
