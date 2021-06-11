//
//  NGCustomUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#ifndef NGCustomUnitControl_hpp
#define NGCustomUnitControl_hpp

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGCustomUnitControl {

protected:
    char* _name;
    bool _initialized;
    bool _logging;
    int _serialRate;
    void _create(char* name, int serialRate);

public:
    void initialize();

};

#endif /* NGCustomUnitControl_h */
