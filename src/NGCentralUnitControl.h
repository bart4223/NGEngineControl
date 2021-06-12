//
//  NGCentralUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGCentralUnitControl_h
#define NGCentralUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>

struct unitStruct
{
    char* name;
    int address;
};
typedef struct unitStruct unit;

class NGCentralUnitControl : public NGCustomUnitControl {
  
private:
    unit _unit[3];
    int _unitCount = 0;

protected:
    int _getUnitAddress(char* name);
    
    void _create(char* name, int address, int serialRate);
        
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, int address);
    
    NGCentralUnitControl(char* name, int address, int serialRate);
    
    void initialize();
    
    void registerUnit(char* name, int address);
    
    void processingLoop();
    
    void sendUnitCommand(char* name, char* command);
    
};

#endif /* NGCentralUnitControl_hpp */
