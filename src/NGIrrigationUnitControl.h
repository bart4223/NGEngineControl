//
//  NGIrrigationUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#ifndef NGIrrigationUnitControl_h
#define NGIrrigationUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGPumpControl.h>
#include <NGSoilMoistureSensor.h>

#define _VERSION "0.7"
#define VERSION (char*)_VERSION

#define MAXIRRIGATIONCOUNT 3
#define MAXPUMPCOUNT MAXIRRIGATIONCOUNT
#define MAXSOILMOISTURESENSORCOUNT MAXIRRIGATIONCOUNT

struct irrigationDataStruct
{
    int soilMoistureSensor;
    int pump;
    int measuringInterval; //seconds
    int wateringTime; //seconds
    int desiccationThreshold;
    unsigned long rtLastMeasuring;
    unsigned long rtLastPumpOn;
    int rtLastDesiccationHumidity;
};
typedef struct irrigationDataStruct irrigationData;

class NGIrrigationUnitControl : public NGCustomUnitControl {

private:
    NGPumpControl *_pumps[MAXPUMPCOUNT];
    int _pumpCount = 0;
    NGSoilMoistureSensor *_soilMoisureSensors[MAXSOILMOISTURESENSORCOUNT];
    int _soilMoistureSensorCount = 0;
    irrigationData _irrigation[MAXIRRIGATIONCOUNT];
    int _irrigationCount = 0;
    unsigned long _secondTick = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);

    void _initializePumps();
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _procesingSecondTick();

    void _procesingIrrigation();

    void _irrigationMeasure(int irrigation);
    
    void _pumpOn(int pump);
    
    void _pumpOff(int pump);
    
    bool _isPumpOn(int pump);
    
    int _getsoilMoistureSensorHumidity(int soilMoistureSensor);
    
public:
    NGIrrigationUnitControl();
    
    NGIrrigationUnitControl(char* name);
                  
    NGIrrigationUnitControl(char* name, byte address);
    
    NGIrrigationUnitControl(char* name, byte address, int serialRate);

    void initialize();
    
    long int startUp();
    
    int registerIrrigation(byte pinPump, byte pinSoilMoistureSensor, int measuringInterval, int wateringTime, int desiccationThreshold);
    
    int registerPump(byte pinPump);

    int registerSoilMoistureSensor(byte pinSoilMoistureSensor);

    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGIrrigationUnitControl_h */
