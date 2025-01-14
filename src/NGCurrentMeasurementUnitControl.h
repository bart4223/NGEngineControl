//
//  NGCurrentMeasurementUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.07.22.
//

#ifndef NGCurrentMeasurementUnitControl_h
#define NGCurrentMeasurementUnitControl_h

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <NGCurrentSensor.h>

#define _VERSION "1.6"
#define VERSION (char*)_VERSION

#define MAXCURRENTSENSORCOUNT 3
#define DEFDISPLAYSENSORINTERVAL 1000
#define MAXAVERAGEMEASUREMENTS 100

struct currentSensorDataStruct
{
    NGCurrentSensor *currentSensor;
    int delay;
    int current;
    int min;
    int max;
    int count = 0;
    long int total = 0;
    int average;
    long int lastTick;
};
typedef struct currentSensorDataStruct currentSensorData;

class NGCurrentMeasurementUnitControl : public NGCustomUnitControl {
  
private:
    currentSensorData _currentSensors[MAXCURRENTSENSORCOUNT];
    int _sensorCount = 0;
    int _lastInfoLen = 0;
    long int _secondTick = 0;
    int _displayedSensor = -1;
    int _displaySensorInterval = DEFDISPLAYSENSORINTERVAL;

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _initializeSensors();
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _procesingCurrentSensors();
    
    void _displayCurrentSensors();
    
    void _processingIRRemoteData();

public:
    NGCurrentMeasurementUnitControl();
    
    NGCurrentMeasurementUnitControl(char* name);
                  
    NGCurrentMeasurementUnitControl(char* name, byte address);
    
    NGCurrentMeasurementUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void setDisplaySensorInterval(int interval);

    int registerSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor, int delay);
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGCurrentMeasurementUnitControl_h */
