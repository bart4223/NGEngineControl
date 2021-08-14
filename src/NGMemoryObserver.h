//
//  NGMemoryObserver.h
//  NGEngineControl
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

#define NODELAY 0

int freeMemory();
void observeMemory(unsigned int sleep);

#ifdef  __cplusplus
}
#endif

#endif /* NGMemoryObserver_h */
