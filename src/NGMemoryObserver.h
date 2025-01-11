//
//  NGMemoryObserver.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.06.21.
//

#ifndef NGMemoryObserver_h
#define NGMemoryObserver_h

#include <Arduino.h>

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
