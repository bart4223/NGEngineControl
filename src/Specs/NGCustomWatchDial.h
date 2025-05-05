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
#include <Specs/NGCustomWatchComplication.h>

struct watchComplicationStruct
{
    NGCustomWatchComplication *complication;
    int delay;
    long lastUpdate = 0;
};
typedef struct watchComplicationStruct watchComplication;

#define MAXWATCHCOMPLICATIONS 3

class NGCustomWatchDial {

protected:
    NGIPaintableComponent *_ipc;
    watchComplication _complications[MAXWATCHCOMPLICATIONS];    
    byte _complicationCount = 0;
    void _create(NGIPaintableComponent *ipc);

public:
    void registerComplication(NGCustomWatchComplication *complication, int delay);

    virtual void initialize();

    virtual void setHour(int hour);

    virtual void setMinute(int minute);

    virtual void setSecond(int second);

    virtual void setTime(int hour, int minute, int second);

    void processingLoop();
};

#endif /* NGCustomWatchDial_h */