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

#define _VERSION "0.2"
#define VERSION (char*)_VERSION

#define MAXPUMPCOUNT 3
#define MAXSOILMOISTURESENSORCOUNT 3

class NGIrrigationUnitControl : public NGCustomUnitControl {

private:
    NGPumpControl *_pumps[MAXPUMPCOUNT];
    NGSoilMoistureSensor *_soilMoisureSensors[MAXSOILMOISTURESENSORCOUNT];
    int _pumpCount = 0;
    int _soilMoistureSensorCount = 0;
    long int _durationSecond = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);

    void _initializePumps();
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
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
    
    int registerPump(byte pinPump);

    int registerSoilMoistureSensor(byte pinSoilMoistureSensor);

    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGIrrigationUnitControl_h */
