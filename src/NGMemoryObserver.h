//
//  NGMemoryObserver.h
//  NGMemoryObserver
//
//  Created by Nils Grimmer on 05.06.21.
//

#ifndef NGMemoryObservere_h
#define NGMemoryObserver_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int freeMemory();

#ifdef  __cplusplus
}
#endif

#endif /* NGMemoryObserver_h */
