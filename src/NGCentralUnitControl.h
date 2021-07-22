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

    int _prepareCommand(byte subject, byte operation, char* name, byte command[]);
    
    void _processingReceivedData();
    
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, byte address);
    
    NGCentralUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void processingLoop();
    
    void registerUnit(char* name, byte address);
    
    void sendUnitEngineRunForward(char* name, char* engine);

    void sendUnitEngineRunBackward(char* name, char* engine);
    
    void sendUnitEngineStop(char* name, char* engine);
    
    void sendUnitEngineSetSpeed(char* name, char* engine, int speed);
    
    void sendUnitJointMove(char* name, char* joint, int targetrad);
    
    void sendUnitJointSimulate(char* name, char* joint);
    
    void sendUnitJointMoveStepToMax(char* name, char* joint);
    
    void sendUnitJointMoveStepToMin(char* name, char* joint);
    
    int receiveUnitJointRead(char* name, char* joint);
    
    void sendUnitGripperRelease(char* name, char* gripper);

    void sendUnitGripperGrip(char* name, char* gripper);

    bool sendUnitCommand(char* name, byte command[], int commandsize);

    void receiveUnitData(char* name);
    
    void requestData(byte* data);
};

#endif /* NGCentralUnitControl_hpp */
