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
    byte address;
};
typedef struct unitStruct unit;

class NGCentralUnitControl : public NGCustomUnitControl {
  
private:
    unit _unit[3];
    int _unitCount = 0;

protected:
    void _create(char* name, byte address, int serialRate);
    
    byte _getUnitAddress(char* name);

    int _prepareCommand(byte subject, byte operation, char* name, int namesize, byte command[]);
        
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, byte address);
    
    NGCentralUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void registerUnit(char* name, byte address);
    
    void sendUnitGripperGrip(char* name, char* gripper, int grippersize);

    void sendUnitGripperRelease(char* name, char* gripper, int grippersize);

    void sendUnitCommand(char* name, byte command[], int commandsize);
    
    void receiveUnitData(char* name);
    
};

#endif /* NGCentralUnitControl_hpp */
