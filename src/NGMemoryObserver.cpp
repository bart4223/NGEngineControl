//
//  NGMemoryObserver.cpp
//  NGMemoryObserver
//
//  Created by Nils Grimmer on 05.06.21.
//

#include "NGMemoryObserver.h"

extern unsigned int __heap_start;
extern void *__brkval;

/*
 * The free list structure as maintained by the
 * avr-libc memory allocation routines.
 */
struct __freelist {
    size_t sz;
    struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

/* Calculates the size of the free list */
int freeListSize() {
    struct __freelist* current;
    int total = 0;
    for (current = __flp; current; current = current->nx) {
        total += 2; /* Add two bytes for the memory block's header  */
        total += (int) current->sz;
    }
    return total;
}

int freeMemory() {
    int free_memory;
    if ((int)__brkval == 0) {
        free_memory = ((int)&free_memory) - ((int)&__heap_start);
    } else {
        free_memory = ((int)&free_memory) - ((int)__brkval);
        free_memory += freeListSize();
    }
    return free_memory;
}

void observeMemory(unsigned int sleep) {
    char log[100];
    sprintf(log, "free Memory %d bytes", freeMemory());
    Serial.println(log);
    if (sleep > 0) {
        delay(sleep);
    }
}
