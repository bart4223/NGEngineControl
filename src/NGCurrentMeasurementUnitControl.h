//
//  NGCurrentMeasurementUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.07.22.
//

#ifndef NGCurrentMeasurementUnitControl_h
#define NGCurrentMeasurementUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGCurrentSensor.h>

#define _VERSION "1.1"
#define VERSION (char*)_VERSION

#define MAXCURRENTSENSORCOUNT 3

struct currentSensorDataStruct
{
    NGCurrentSensor *currentSensor;
    int delay;
    long int lastTick;
};
typedef struct currentSensorDataStruct currentSensorData;

class NGCurrentMeasurementUnitControl : public NGCustomUnitControl {
  
private:
    currentSensorData _currentSensors[MAXCURRENTSENSORCOUNT];
    int _sensorCount = 0;
    int _lastInfoLen = 0;

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _initializeSensors();
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _procesingCurrentSensors();

public:
    NGCurrentMeasurementUnitControl();
    
    NGCurrentMeasurementUnitControl(char* name);
                  
    NGCurrentMeasurementUnitControl(char* name, byte address);
    
    NGCurrentMeasurementUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    int registerSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor, int delay);
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGCurrentMeasurementUnitControl_h */
