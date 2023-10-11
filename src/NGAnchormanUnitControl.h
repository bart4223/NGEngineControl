//
//  NGAnchormanUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.23.
//

#ifndef NGAnchormanUnitControl_h
#define NGAnchormanUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGEngineControl.h>

#define _VERSION "0.8"
#define VERSION (char*)_VERSION

#define MAXTURNTABLECOUNT 3
#define MAXTURNTABLEMOTIONPROFILECOUNT 3
#define NOTURNTABLEMOTIONPROFILE -1
#define MAXTURNTABLEMOTIONPROFILESTEPCOUNT 10
#define NOTURNTABLECURRENTSTEP -1

enum turnTableMotionProfileKind { ttmpkSimple };

struct turnTableMotionProfileStruct
{
    turnTableMotionProfileKind kind;
    long steps[MAXTURNTABLEMOTIONPROFILESTEPCOUNT];
    byte count = 0;
};
typedef struct turnTableMotionProfileStruct turnTableMotionProfile;

struct turnTableStruct
{
    NGEngineControl *engine;
    byte speed;
    int delay;
    int profile;
    int currentstep;
    long laststep;
};
typedef struct turnTableStruct turnTable;

class NGAnchormanUnitControl : public NGCustomUnitControl {

private:
    turnTable _turnTables[MAXTURNTABLECOUNT];
    turnTableMotionProfile _turnTableMotionProfiles[MAXTURNTABLEMOTIONPROFILECOUNT];
    int _turnTableCount = 0;
    int _turnTableMotionProfileCount = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
public:
    NGAnchormanUnitControl();
    
    NGAnchormanUnitControl(char* name);
                  
    NGAnchormanUnitControl(char* name, byte address);
    
    NGAnchormanUnitControl(char* name, byte address, int serialRate);
    
    byte registerSimpleTurnTableMotionProfile(long stepForwardRun, long stepForwardStop, long stepBackwardRun, long stepBackwardStop);
    
    byte registerTurnTable(NGEngineControl* engine, byte speed, int delay, int profile);
    
    void initialize();
    
    void processingLoop();
    
    void incrementMotionProfileStep(byte profile, byte step, int count);
    
    void decrementMotionProfileStep(byte profile, byte step, int count);
    
    void requestData(byte* data);
};

#endif /* NGAnchormanUnitControl_h */
