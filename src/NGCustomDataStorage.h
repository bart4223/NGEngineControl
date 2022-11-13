//
//  NGCustomDataStorage.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.11.22.
//

#ifndef NGCustomDataStorage_h
#define NGCustomDataStorage_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGCustomDataStorage {
  
protected:
    bool _initialized = false;
    bool _logging = false;
    
public:
    void setLogging(bool logging);
    
    bool getLogging();
    
    virtual void initialize();
    
    virtual void open();
    
    virtual void close();
};

#endif /* NGCustomDataStorage_h */
