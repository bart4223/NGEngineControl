//
//  NGCustomWatchDial.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.04.25.
//

#ifndef NGCustomWatchDial_h
#define NGCustomWatchDial_h

#include <Arduino.h>
#include <NGIPaintableComponent.h>

class NGCustomWatchDial {

protected:
    NGIPaintableComponent *_ipc;
    
    void _create(NGIPaintableComponent *ipc);

public:
    virtual void initialize();

    virtual void setHour(int hour);

    virtual void setMinute(int minute);

    virtual void setSecond(int second);

    virtual void setTime(int hour, int minute, int second);
};

#endif /* NGCustomWatchDial_h */